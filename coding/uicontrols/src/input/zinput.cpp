#include "zinput.h"
#include "theme/theme.h"

#include <QEvent>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>

ZInput::ZInput(QWidget* parent)
    : QWidget(parent)
{
    // Inner line edit
    edit_ = new QLineEdit(this);
    edit_->setFrame(false);
    QPalette pal = edit_->palette();
    pal.setColor(QPalette::Base, Qt::transparent);
    pal.setColor(QPalette::PlaceholderText, QColor(0xa8, 0xab, 0xb2));
    edit_->setPalette(pal);

    edit_->installEventFilter(this);

    setFocusProxy(edit_);  // click anywhere on ZInput → focus inner QLineEdit

    // Clear button
    clear_btn_ = new QPushButton(QString(QChar(0x00D7)), this);
    clear_btn_->setFixedSize(16, 16);
    clear_btn_->setFlat(true);
    clear_btn_->setCursor(Qt::PointingHandCursor);
    clear_btn_->setVisible(false);
    {
        QPalette bp = clear_btn_->palette();
        bp.setColor(QPalette::ButtonText, QColor(0x90, 0x93, 0x99));
        clear_btn_->setPalette(bp);
    }
    clear_btn_->installEventFilter(this);

    // Password toggle button
    password_btn_ = new QPushButton(this);
    password_btn_->setFixedSize(16, 16);
    password_btn_->setFlat(true);
    password_btn_->setCursor(Qt::PointingHandCursor);
    password_btn_->setVisible(false);
    {
        QPalette bp = password_btn_->palette();
        bp.setColor(QPalette::ButtonText, QColor(0x90, 0x93, 0x99));
        password_btn_->setPalette(bp);
    }
    password_btn_->installEventFilter(this);

    // Layout
    auto* lay = new QHBoxLayout(this);
    lay->setContentsMargins(8, 1, 8, 1);
    lay->setSpacing(4);
    lay->addWidget(edit_, 1);
    lay->addWidget(clear_btn_);
    lay->addWidget(password_btn_);

    // Signals
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
        password_btn_->setText(hidden ? QString(QChar(0x25C9)) : QString(QChar(0x25CB)));
    });

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    updateLayout();
}

void ZInput::setText(const QString& text)           { edit_->setText(text); }
QString ZInput::text() const                        { return edit_->text(); }
void ZInput::setPlaceholderText(const QString& t)   { edit_->setPlaceholderText(t); }
QString ZInput::placeholderText() const             { return edit_->placeholderText(); }

void ZInput::setInputSize(InputSize size)
{
    size_ = size;
    updateLayout();
    update();
}

void ZInput::setClearable(bool clearable)
{
    clearable_ = clearable;
    updateClearButton();
}

void ZInput::setPasswordMode(bool password)
{
    password_mode_ = password;
    password_btn_->setVisible(password_mode_);
    if (password_mode_) {
        edit_->setEchoMode(QLineEdit::Password);
        password_btn_->setText(QString(QChar(0x25CB))); // ○ show
    } else {
        edit_->setEchoMode(QLineEdit::Normal);
    }
}

ZInput::InputSize ZInput::inputSize() const         { return size_; }
bool ZInput::isClearable() const                    { return clearable_; }
bool ZInput::isPasswordMode() const                 { return password_mode_; }
QLineEdit* ZInput::lineEdit() const                 { return edit_; }

void ZInput::updateLayout()
{
    static const int heights[] = {40, 32, 24};
    static const int fontSizes[] = {14, 14, 12};
    int h = heights[size_];
    int fs = fontSizes[size_];

    setMinimumHeight(h);
    setFixedHeight(h);

    QFont f = font();
    f.setPixelSize(fs);
    setFont(f);
    edit_->setFont(f);
}

void ZInput::updateClearButton()
{
    clear_btn_->setVisible(clearable_ && !edit_->text().isEmpty());
}

static void setBtnTextColor(QPushButton* btn, const QColor& c)
{
    QPalette bp = btn->palette();
    bp.setColor(QPalette::ButtonText, c);
    btn->setPalette(bp);
}

bool ZInput::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == edit_) {
        if (event->type() == QEvent::Enter) {
            hovered_ = true;
            update();
        } else if (event->type() == QEvent::Leave) {
            hovered_ = false;
            update();
        }
    } else if (obj == clear_btn_ || obj == password_btn_) {
        auto* btn = static_cast<QPushButton*>(obj);
        if (event->type() == QEvent::Enter) {
            setBtnTextColor(btn, theme::colorPrimary());
        } else if (event->type() == QEvent::Leave) {
            setBtnTextColor(btn, QColor(0x90, 0x93, 0x99));
        }
    }
    return QWidget::eventFilter(obj, event);
}

void ZInput::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    qreal radius = theme::borderRadiusBase();
    qreal bw = 1.0;

    QColor bg = isEnabled() ? theme::colorWhite() : theme::fillLight();

    // Border color
    QColor border;
    if (!isEnabled()) {
        border = theme::borderLight();
    } else if (edit_->hasFocus()) {
        border = theme::colorPrimary();
        // Focus glow ring
        QColor glow = theme::colorPrimary();
        glow.setAlpha(38);
        QPainterPath glowPath;
        glowPath.addRoundedRect(QRectF(r).adjusted(-1.5, -1.5, 1.5, 1.5),
                                radius + 2, radius + 2);
        p.setPen(QPen(glow, 2));
        p.setBrush(Qt::NoBrush);
        p.drawPath(glowPath);
    } else if (hovered_) {
        border = theme::primaryLight7();
    } else {
        border = theme::borderColor();
    }

    // Background fill
    QPainterPath bgPath;
    bgPath.addRoundedRect(QRectF(r).adjusted(bw, bw, -bw, -bw), radius, radius);
    p.setPen(Qt::NoPen);
    p.setBrush(bg);
    p.drawPath(bgPath);

    // Border
    QPainterPath borderPath;
    borderPath.addRoundedRect(QRectF(r).adjusted(bw / 2, bw / 2, -bw / 2, -bw / 2),
                              radius, radius);
    p.setPen(QPen(border, bw));
    p.setBrush(Qt::NoBrush);
    p.drawPath(borderPath);
}
