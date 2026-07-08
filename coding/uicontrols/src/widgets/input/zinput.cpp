#include "zinput.h"

#include <QEvent>
#include <QFrame>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPainter>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "painter/painter.h"

// Icon button for clear / password-toggle — uses Theme colors via Painter
namespace {

class IconButton : public QPushButton {
public:
    using QPushButton::QPushButton;
protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setPen(hovered_ ? theme::colorPrimary() : theme::textRegular());
        p.setFont(font());
        p.drawText(rect(), Qt::AlignCenter, text());
    }
    void enterEvent(QEvent*) override { hovered_ = true; update(); }
    void leaveEvent(QEvent*) override { hovered_ = false; update(); }
private:
    bool hovered_ = false;
};

} // namespace

// ─── Construction ────────────────────────────────────────────────────

ZInput::ZInput(QWidget* parent)
    : QWidget(parent)
    , state_tracker_(new statemachine::StateTracker(this))
{
    edit_ = new QLineEdit(this);
    edit_->setFrame(false);
    QPalette pal = edit_->palette();
    pal.setColor(QPalette::Base, Qt::transparent);
    pal.setColor(QPalette::PlaceholderText, theme::textDisabled());
    edit_->setPalette(pal);

    edit_->installEventFilter(this);
    setFocusProxy(edit_);

    clear_btn_ = new IconButton(QString(theme::icon::close()), this);
    clear_btn_->setFixedSize(16, 16);
    clear_btn_->setFlat(true);
    clear_btn_->setCursor(Qt::PointingHandCursor);
    clear_btn_->setVisible(false);

    password_btn_ = new IconButton(this);
    password_btn_->setFixedSize(16, 16);
    password_btn_->setFlat(true);
    password_btn_->setCursor(Qt::PointingHandCursor);
    password_btn_->setVisible(false);

    auto* lay = new QHBoxLayout(this);
    lay->setContentsMargins(8, 1, 8, 1);
    lay->setSpacing(4);
    lay->addWidget(edit_, 1);
    lay->addWidget(clear_btn_);
    lay->addWidget(password_btn_);

    connect(edit_, &QLineEdit::textChanged, this, [this]() {
        updateClearButton();
        emit textChanged(edit_->text());
    });
    connect(clear_btn_, &QPushButton::clicked, this, [this]() {
        edit_->clear();
        edit_->setFocus();
    });
    connect(password_btn_, &QPushButton::clicked, this, [this]() {
        bool hidden = (edit_->echoMode() == QLineEdit::Password);
        edit_->setEchoMode(hidden ? QLineEdit::Normal : QLineEdit::Password);
        password_btn_->setText(hidden ? QString(theme::icon::eye()) : QString(theme::icon::eyeSlash()));
    });

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    updateLayout();
}

// ─── Public setters / getters ────────────────────────────────────────

void ZInput::setText(const QString& text)           { edit_->setText(text); }
QString ZInput::text() const                        { return edit_->text(); }
void ZInput::setPlaceholderText(const QString& t)   { edit_->setPlaceholderText(t); }
QString ZInput::placeholderText() const             { return edit_->placeholderText(); }

void ZInput::setInputSize(InputSize size) {
    size_ = size;
    updateLayout();
    update();
}

void ZInput::setClearable(bool clearable) {
    clearable_ = clearable;
    updateClearButton();
}

void ZInput::setPasswordMode(bool password) {
    password_mode_ = password;
    password_btn_->setVisible(password_mode_);
    if (password_mode_) {
        edit_->setEchoMode(QLineEdit::Password);
        password_btn_->setText(QString(theme::icon::eyeSlash()));
    } else {
        edit_->setEchoMode(QLineEdit::Normal);
    }
}

void ZInput::setTextarea(int rows) {
    rows_ = rows;
    if (!textarea_) {
        textarea_ = new QPlainTextEdit(this);
        textarea_->setFrameShape(QFrame::NoFrame);
        textarea_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textarea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textarea_->document()->setDocumentMargin(0);
        QPalette tp = textarea_->palette();
        tp.setColor(QPalette::Base, Qt::transparent);
        tp.setColor(QPalette::PlaceholderText, theme::textDisabled());
        textarea_->setPalette(tp);
        textarea_->installEventFilter(this);
        textarea_->setVisible(false);

        auto* lay = qobject_cast<QHBoxLayout*>(layout());
        if (lay) {
            int idx = lay->indexOf(edit_);
            lay->insertWidget(idx + 1, textarea_, 1);
        }

        connect(textarea_, &QPlainTextEdit::textChanged, this, [this]() {
            emit textChanged(textarea_->toPlainText());
        });
    }

    edit_->setVisible(false);
    textarea_->setVisible(true);

    int lineHeight = QFontMetrics(textarea_->font()).lineSpacing();
    textarea_->setFixedHeight(rows * lineHeight + 8);
    textarea_->setPlaceholderText(placeholderText());

    setFixedHeight(rows * lineHeight + 10);
    setFocusProxy(textarea_);
    update();
}

void ZInput::setPrefixIcon(const QChar& icon) {
    prefix_icon_ = icon;
    auto* lay = qobject_cast<QHBoxLayout*>(layout());
    if (lay && !icon.isNull()) {
        lay->setContentsMargins(28, 1, 8, 1);
    } else if (lay) {
        lay->setContentsMargins(8, 1, 8, 1);
    }
    update();
}

void ZInput::setSuffixIcon(const QChar& icon) {
    suffix_icon_ = icon;
    auto* lay = qobject_cast<QHBoxLayout*>(layout());
    if (lay && !icon.isNull()) {
        lay->setContentsMargins(lay->contentsMargins().left(), 1, 28, 1);
    }
    update();
}

ZInput::InputSize ZInput::inputSize() const          { return size_; }
bool ZInput::isClearable() const                     { return clearable_; }
bool ZInput::isPasswordMode() const                  { return password_mode_; }
QLineEdit* ZInput::lineEdit() const                  { return edit_; }

// ─── Layout ──────────────────────────────────────────────────────────

void ZInput::updateLayout() {
    theme::SizeSpec s = theme::inputSize(size_);

    setMinimumHeight(s.height);
    setFixedHeight(s.height);

    QFont f = font();
    f.setPixelSize(s.fontSize);
    setFont(f);
    edit_->setFont(f);
    if (textarea_) {
        textarea_->setFont(f);
    }
}

void ZInput::updateClearButton() {
    clear_btn_->setVisible(clearable_ && !edit_->text().isEmpty());
}

// ─── Events ──────────────────────────────────────────────────────────

bool ZInput::eventFilter(QObject* obj, QEvent* event) {
    if (obj == edit_ || obj == textarea_) {
        switch (event->type()) {
        case QEvent::Enter:
            state_tracker_->SetHovered(true);
            state_tracker_->Update();
            update();
            break;
        case QEvent::Leave:
            state_tracker_->SetHovered(false);
            state_tracker_->Update();
            update();
            break;
        case QEvent::FocusIn:
            state_tracker_->SetFocused(true);
            state_tracker_->Update();
            update();
            break;
        case QEvent::FocusOut:
            state_tracker_->SetFocused(false);
            state_tracker_->Update();
            update();
            break;
        default:
            break;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void ZInput::changeEvent(QEvent*) {
    state_tracker_->SetEnabled(isEnabled());
    state_tracker_->Update();
    update();
}

// ─── Painting ────────────────────────────────────────────────────────

void ZInput::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    qreal radius = theme::borderRadiusBase();

    statemachine::ComponentState compState = state_tracker_->CurrentState();
    bool disabled = (compState == statemachine::ComponentState::kDisabled);
    bool hovered = (compState == statemachine::ComponentState::kHover);
    // Focus check: use inner widget's real focus, not StateTracker's resolved priority
    // StateTracker puts kHover > kFocused, but input should show focus ring when focused
    QWidget* focusWidget = textarea_ && textarea_->isVisible()
        ? static_cast<QWidget*>(textarea_) : static_cast<QWidget*>(edit_);
    bool focused = focusWidget && focusWidget->hasFocus();

    // Background
    QColor bg = disabled ? theme::fillLight() : theme::colorWhite();
    painter::DrawBackground(p, r, bg, radius);

    // Border
    QColor border;
    if (disabled) {
        border = theme::borderLight();
    } else if (focused) {
        border = theme::colorPrimary();
        // Focus glow ring
        painter::DrawFocusRing(p, QRectF(r).adjusted(-2, -2, 2, 2),
                                radius + 2, theme::focusOutline());
    } else if (hovered) {
        border = theme::primaryLight7();
    } else {
        border = theme::borderColor();
    }

    QRectF borderRect = QRectF(r).adjusted(0.5, 0.5, -0.5, -0.5);
    painter::DrawBorder(p, borderRect, border, 1.0, radius);

    // Prefix icon
    if (!prefix_icon_.isNull()) {
        QFont f = p.font();
        f.setPixelSize(14);
        p.setPen(theme::textRegular());
        p.setFont(f);
        p.drawText(QRect(8, 0, 16, height()), Qt::AlignCenter, QString(prefix_icon_));
    }

    // Suffix icon
    if (!suffix_icon_.isNull()) {
        QFont f = p.font();
        f.setPixelSize(14);
        p.setPen(theme::textRegular());
        p.setFont(f);
        p.drawText(QRect(width() - 24, 0, 16, height()), Qt::AlignCenter, QString(suffix_icon_));
    }
}
