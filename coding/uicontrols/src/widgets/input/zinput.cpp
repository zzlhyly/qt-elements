#include "zinput.h"

#include <QEvent>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "painter/painter.h"

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

    word_limit_label_ = new QLabel(this);
    word_limit_label_->setVisible(false);
    QFont wf = word_limit_label_->font();
    wf.setPixelSize(12);
    word_limit_label_->setFont(wf);

    auto* outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    outer->setSpacing(2);

    auto* lay = new QHBoxLayout();
    lay->setContentsMargins(8, 1, 8, 1);
    lay->setSpacing(4);
    lay->addWidget(edit_, 1);
    lay->addWidget(clear_btn_);
    lay->addWidget(password_btn_);
    outer->addLayout(lay);
    outer->addWidget(word_limit_label_, 0, Qt::AlignRight);

    connect(edit_, &QLineEdit::textChanged, this, [this]() {
        updateClearButton();
        updateWordLimit();
        emit textChanged(edit_->text());
    });
    connect(clear_btn_, &QPushButton::clicked, this, [this]() { edit_->clear(); edit_->setFocus(); });
    connect(password_btn_, &QPushButton::clicked, this, [this]() {
        bool hidden = (edit_->echoMode() == QLineEdit::Password);
        edit_->setEchoMode(hidden ? QLineEdit::Normal : QLineEdit::Password);
        password_btn_->setText(hidden ? QString(theme::icon::eye()) : QString(theme::icon::eyeSlash()));
    });

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    updateLayout();
}

void ZInput::setText(const QString& text)           { edit_->setText(text); }
QString ZInput::text() const                        { return edit_->text(); }
void ZInput::setPlaceholderText(const QString& t)   { edit_->setPlaceholderText(t); }
QString ZInput::placeholderText() const             { return edit_->placeholderText(); }

void ZInput::setInputSize(InputSize size) { size_ = size; updateLayout(); update(); }
void ZInput::setClearable(bool clearable) { clearable_ = clearable; updateClearButton(); }

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

        auto* lay = findChild<QHBoxLayout*>();
        if (lay) {
            int idx = lay->indexOf(edit_);
            lay->insertWidget(idx + 1, textarea_, 1);
        }
        connect(textarea_, &QPlainTextEdit::textChanged, this, [this]() {
            updateWordLimit();
            emit textChanged(textarea_->toPlainText());
        });
    }
    edit_->setVisible(false);
    textarea_->setVisible(true);
    updateLayout();
    setFocusProxy(textarea_);
    update();
}

void ZInput::setPrefixIcon(const QChar& icon) {
    prefix_icon_ = icon;
    auto* lay = findChild<QHBoxLayout*>();
    if (lay) lay->setContentsMargins(icon.isNull() ? 8 : 28, 1, lay->contentsMargins().right(), 1);
    update();
}

void ZInput::setSuffixIcon(const QChar& icon) {
    suffix_icon_ = icon;
    auto* lay = findChild<QHBoxLayout*>();
    if (lay) lay->setContentsMargins(lay->contentsMargins().left(), 1, icon.isNull() ? 8 : 28, 1);
    update();
}

void ZInput::setPrependWidget(QWidget* widget) {
    auto* lay = findChild<QHBoxLayout*>();
    if (!lay) return;
    if (prepend_widget_) lay->removeWidget(prepend_widget_);
    prepend_widget_ = widget;
    if (widget) lay->insertWidget(0, widget);
}

void ZInput::setAppendWidget(QWidget* widget) {
    auto* lay = findChild<QHBoxLayout*>();
    if (!lay) return;
    if (append_widget_) lay->removeWidget(append_widget_);
    append_widget_ = widget;
    if (widget) lay->addWidget(widget);
}

void ZInput::setAutosize(bool autosize) {
    autosize_ = autosize;
    if (autosize_ && textarea_) textarea_->setFixedHeight(QWIDGETSIZE_MAX);
    else if (textarea_) updateLayout();
}

void ZInput::setAutosizeMinRows(int rows) { autosize_min_rows_ = qMax(1, rows); }
void ZInput::setAutosizeMaxRows(int rows) { autosize_max_rows_ = qMax(autosize_min_rows_, rows); }

void ZInput::setShowWordLimit(bool show) {
    show_word_limit_ = show;
    word_limit_label_->setVisible(show);
    updateWordLimit();
}

void ZInput::setMaxLength(int len) { max_length_ = len; updateWordLimit(); }

ZInput::InputSize ZInput::inputSize() const { return size_; }
bool ZInput::isClearable() const            { return clearable_; }
bool ZInput::isPasswordMode() const         { return password_mode_; }
QLineEdit* ZInput::lineEdit() const         { return edit_; }

void ZInput::updateLayout() {
    theme::SizeSpec s = theme::inputSize(size_);
    setMinimumHeight(s.height);
    if (!autosize_) setFixedHeight(s.height);
    QFont f = font();
    f.setPixelSize(s.fontSize);
    setFont(f); edit_->setFont(f);
    if (textarea_) {
        textarea_->setFont(f);
        if (!autosize_) {
            int lh = QFontMetrics(f).lineSpacing();
            textarea_->setFixedHeight(rows_ * lh + 8);
            setFixedHeight(rows_ * lh + 10);
        }
    }
}

void ZInput::updateClearButton() {
    clear_btn_->setVisible(clearable_ && !edit_->text().isEmpty());
}

void ZInput::updateWordLimit() {
    if (!show_word_limit_ || max_length_ <= 0) return;
    int len = textarea_ && textarea_->isVisible() ? textarea_->toPlainText().length() : edit_->text().length();
    word_limit_label_->setText(QString::number(len) + " / " + QString::number(max_length_));
}

bool ZInput::eventFilter(QObject* obj, QEvent* event) {
    if (obj == edit_ || obj == textarea_) {
        switch (event->type()) {
        case QEvent::Enter: state_tracker_->SetHovered(true); state_tracker_->Update(); update(); break;
        case QEvent::Leave: state_tracker_->SetHovered(false); state_tracker_->Update(); update(); break;
        case QEvent::FocusIn: state_tracker_->SetFocused(true); state_tracker_->Update(); update(); break;
        case QEvent::FocusOut: state_tracker_->SetFocused(false); state_tracker_->Update(); update(); break;
        default: break;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void ZInput::changeEvent(QEvent*) {
    state_tracker_->SetEnabled(isEnabled());
    state_tracker_->Update();
    update();
}

void ZInput::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    qreal radius = theme::borderRadiusBase();

    statemachine::ComponentState compState = state_tracker_->CurrentState();
    bool disabled = (compState == statemachine::ComponentState::kDisabled);
    bool hovered = (compState == statemachine::ComponentState::kHover);
    QWidget* focusWidget = textarea_ && textarea_->isVisible()
        ? static_cast<QWidget*>(textarea_) : static_cast<QWidget*>(edit_);
    bool focused = focusWidget && focusWidget->hasFocus();

    QColor bg = disabled ? theme::fillLight() : theme::colorWhite();
    painter::DrawBackground(p, r, bg, radius);

    QColor border;
    if (disabled) border = theme::borderLight();
    else if (focused) { border = theme::colorPrimary(); painter::DrawFocusRing(p, QRectF(r).adjusted(-2, -2, 2, 2), radius + 2, theme::focusOutline()); }
    else if (hovered) border = theme::primaryLight7();
    else border = theme::borderColor();

    painter::DrawBorder(p, QRectF(r).adjusted(0.5, 0.5, -0.5, -0.5), border, 1.0, radius);

    if (!prefix_icon_.isNull()) { QFont f = p.font(); f.setPixelSize(14); p.setPen(theme::textRegular()); p.setFont(f); p.drawText(QRect(8, 0, 16, height()), Qt::AlignCenter, QString(prefix_icon_)); }
    if (!suffix_icon_.isNull()) { QFont f = p.font(); f.setPixelSize(14); p.setPen(theme::textRegular()); p.setFont(f); p.drawText(QRect(width() - 24, 0, 16, height()), Qt::AlignCenter, QString(suffix_icon_)); }
}
