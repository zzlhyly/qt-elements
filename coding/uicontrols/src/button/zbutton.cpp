#include "zbutton.h"

#include <QFontMetrics>
#include <QKeyEvent>
#include <QPainter>
#include <QPainterPath>

// --- Color tables: [ButtonType][state 0=normal,1=hover,2=pressed,3=disabled] ---

static const QColor solidBg[6][4] = {
    { {0xff,0xff,0xff}, {0xec,0xf5,0xff}, {0xec,0xf5,0xff}, {0xff,0xff,0xff} }, // Default
    { {0x40,0x9e,0xff}, {0x79,0xbb,0xff}, {0x33,0x7e,0xcc}, {0xa0,0xcf,0xff} }, // Primary
    { {0x67,0xc2,0x3a}, {0x95,0xd4,0x75}, {0x52,0x9b,0x2e}, {0xb3,0xe1,0x9d} }, // Success
    { {0xe6,0xa2,0x3c}, {0xf0,0xc7,0x8a}, {0xb8,0x82,0x30}, {0xf3,0xd1,0x9e} }, // Warning
    { {0xf5,0x6c,0x6c}, {0xf8,0x9c,0x9c}, {0xc4,0x56,0x56}, {0xfa,0xb6,0xb6} }, // Danger
    { {0x90,0x93,0x99}, {0xa6,0xa9,0xad}, {0x73,0x76,0x7a}, {0xc4,0xc7,0xcc} }, // Info
};

static const QColor solidText[6][4] = {
    { {0x60,0x62,0x66}, {0x40,0x9e,0xff}, {0x40,0x9e,0xff}, {0xc0,0xc4,0xcc} }, // Default
    { {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0xff,0xff,0xff} }, // Primary
    { {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0xff,0xff,0xff} }, // Success
    { {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0xff,0xff,0xff} }, // Warning
    { {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0xff,0xff,0xff} }, // Danger
    { {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0xff,0xff,0xff} }, // Info
};

static const QColor solidBorder[6][4] = {
    { {0xdc,0xdf,0xe6}, {0xc6,0xe2,0xff}, {0x40,0x9e,0xff}, {0xe4,0xe7,0xed} }, // Default
    { {0x40,0x9e,0xff}, {0x79,0xbb,0xff}, {0x33,0x7e,0xcc}, {0xa0,0xcf,0xff} }, // Primary
    { {0x67,0xc2,0x3a}, {0x95,0xd4,0x75}, {0x52,0x9b,0x2e}, {0xb3,0xe1,0x9d} }, // Success
    { {0xe6,0xa2,0x3c}, {0xf0,0xc7,0x8a}, {0xb8,0x82,0x30}, {0xf3,0xd1,0x9e} }, // Warning
    { {0xf5,0x6c,0x6c}, {0xf8,0x9c,0x9c}, {0xc4,0x56,0x56}, {0xfa,0xb6,0xb6} }, // Danger
    { {0x90,0x93,0x99}, {0xa6,0xa9,0xad}, {0x73,0x76,0x7a}, {0xc4,0xc7,0xcc} }, // Info
};

static const QColor plainBg[5][4] = {
    { {0xec,0xf5,0xff}, {0x40,0x9e,0xff}, {0x33,0x7e,0xcc}, {0xec,0xf5,0xff} }, // Primary
    { {0xf5,0xfa,0xed}, {0x67,0xc2,0x3a}, {0x52,0x9b,0x2e}, {0xf5,0xfa,0xed} }, // Success
    { {0xfd,0xf8,0xde}, {0xe6,0xa2,0x3c}, {0xb8,0x82,0x30}, {0xfd,0xf8,0xde} }, // Warning
    { {0xfe,0xf5,0xf5}, {0xf5,0x6c,0x6c}, {0xc4,0x56,0x56}, {0xfe,0xf5,0xf5} }, // Danger
    { {0xf8,0xf9,0xfa}, {0x90,0x93,0x99}, {0x73,0x76,0x7a}, {0xf8,0xf9,0xfa} }, // Info
};

static const QColor plainText[5][4] = {
    { {0x40,0x9e,0xff}, {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0x79,0xbb,0xff} }, // Primary
    { {0x67,0xc2,0x3a}, {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0x95,0xd4,0x75} }, // Success
    { {0xe6,0xa2,0x3c}, {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0xf0,0xc7,0x8a} }, // Warning
    { {0xf5,0x6c,0x6c}, {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0xf8,0x9c,0x9c} }, // Danger
    { {0x90,0x93,0x99}, {0xff,0xff,0xff}, {0xff,0xff,0xff}, {0xa6,0xa9,0xad} }, // Info
};

static const QColor plainBorder[5][4] = {
    { {0xa0,0xcf,0xff}, {0x40,0x9e,0xff}, {0x33,0x7e,0xcc}, {0xd9,0xec,0xff} }, // Primary
    { {0xb3,0xe1,0x9d}, {0x67,0xc2,0x3a}, {0x52,0x9b,0x2e}, {0xe1,0xf3,0xd8} }, // Success
    { {0xf5,0xde,0x9e}, {0xe6,0xa2,0x3c}, {0xb8,0x82,0x30}, {0xfa,0xec,0xd8} }, // Warning
    { {0xfc,0xd2,0xd2}, {0xf5,0x6c,0x6c}, {0xc4,0x56,0x56}, {0xfd,0xe2,0xe2} }, // Danger
    { {0xd0,0xd3,0xd8}, {0x90,0x93,0x99}, {0x73,0x76,0x7a}, {0xe1,0xe4,0xe8} }, // Info
};

// Text variant colors per type (normal state)
static const QColor textVarText[6] = {
    {0x60,0x62,0x66}, {0x40,0x9e,0xff}, {0x67,0xc2,0x3a}, {0xe6,0xa2,0x3c}, {0xf5,0x6c,0x6c}, {0x90,0x93,0x99}
};

ZButton::ZButton(QWidget* parent)
    : QAbstractButton(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::StrongFocus);
}

ZButton::ZButton(const QString& text, QWidget* parent)
    : QAbstractButton(parent)
{
    setText(text);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::StrongFocus);
}

void ZButton::setButtonType(ButtonType type)   { type_ = type; update(); }
void ZButton::setButtonSize(ButtonSize size)   { size_ = size; updateGeometry(); update(); }
void ZButton::setButtonVariant(ButtonVariant v) { variant_ = v; update(); }
void ZButton::setRound(bool r)                 { round_ = r; update(); }
void ZButton::setCircle(bool c)                { circle_ = c; updateGeometry(); update(); }

ZButton::ButtonType ZButton::buttonType() const     { return type_; }
ZButton::ButtonSize ZButton::buttonSize() const      { return size_; }
ZButton::ButtonVariant ZButton::buttonVariant() const { return variant_; }
bool ZButton::isRound() const                        { return round_; }
bool ZButton::isCircle() const                       { return circle_; }

const ZButton::SizeSpec& ZButton::sizeSpec() const
{
    static const SizeSpec specs[] = {
        { 40, 14, 4, 20, 1, 8 }, // Large
        { 32, 14, 4, 16, 1, 6 }, // Default
        { 24, 12, 3, 12, 1, 4 }, // Small
    };
    return specs[size_];
}

qreal ZButton::borderRadius() const
{
    if (circle_) return height() / 2.0;
    if (round_) return 20.0;
    return sizeSpec().radius;
}

QColor ZButton::bgColor() const
{
    if (variant_ == kText) {
        if (!isEnabled()) return Qt::transparent;
        if (isDown()) return QColor(0xf0, 0xf2, 0xf5);
        if (hovered_) return QColor(0xf5, 0xf7, 0xfa);
        return Qt::transparent;
    }

    int si = !isEnabled() ? 3 : isDown() ? 2 : hovered_ ? 1 : 0;

    if (variant_ == kSolid) {
        if (type_ == kDefault) return solidBg[0][si];
        return solidBg[type_][si];
    }

    // Plain
    if (type_ == kDefault) {
        // plain default uses solid default bg
        return solidBg[0][si];
    }
    return plainBg[type_ - 1][si];
}

QColor ZButton::textColor() const
{
    if (variant_ == kText) {
        if (!isEnabled()) return QColor(0xc0, 0xc4, 0xcc);
        return textVarText[type_];
    }

    int si = !isEnabled() ? 3 : isDown() ? 2 : hovered_ ? 1 : 0;

    if (variant_ == kSolid) {
        if (type_ == kDefault) return solidText[0][si];
        return solidText[type_][si];
    }

    // Plain
    if (type_ == kDefault) return solidText[0][si];
    return plainText[type_ - 1][si];
}

QColor ZButton::borderColor() const
{
    if (variant_ == kText) return Qt::transparent;

    int si = !isEnabled() ? 3 : isDown() ? 2 : hovered_ ? 1 : 0;

    if (variant_ == kSolid) {
        if (type_ == kDefault) return solidBorder[0][si];
        return solidBorder[type_][si];
    }

    // Plain
    if (type_ == kDefault) return solidBorder[0][si];
    return plainBorder[type_ - 1][si];
}

QSize ZButton::sizeHint() const
{
    const SizeSpec& s = sizeSpec();
    QFont f = font();
    f.setPixelSize(s.fontSize);
    f.setWeight(QFont::Medium);
    QFontMetrics fm(f);

    int w = 0;
    if (circle_) {
        w = s.height;
    } else {
        if (!text().isEmpty()) w += fm.horizontalAdvance(text());
        if (!icon().isNull()) {
            int iconSize = s.height - 8;
            w += iconSize;
            if (!text().isEmpty()) w += s.iconGap;
        }
        if (!circle_) w += s.padH * 2;
        w = qMax(w, s.height);
    }
    return QSize(w, s.height);
}

QSize ZButton::minimumSizeHint() const
{
    const SizeSpec& s = sizeSpec();
    if (circle_) return QSize(s.height, s.height);
    return QSize(s.height, s.height);
}

void ZButton::paintEvent(QPaintEvent*)
{
    const SizeSpec& s = sizeSpec();
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Font setup
    QFont f = font();
    f.setPixelSize(s.fontSize);
    f.setWeight(QFont::Medium);
    p.setFont(f);

    QRect r = rect();
    qreal radius = borderRadius();
    qreal bw = s.border;

    // Background + border
    QPainterPath path;
    path.addRoundedRect(QRectF(r).adjusted(bw/2, bw/2, -bw/2, -bw/2), radius, radius);

    QColor bg = bgColor();
    QColor bc = borderColor();

    if (variant_ == kText) {
        // Text variant: fill only, no border
        p.fillPath(path, bg);
    } else {
        p.setPen(QPen(bc, bw));
        p.setBrush(bg);
        p.drawPath(path);
    }

    // Focus ring
    if (hasFocus() && !circle_) {
        p.setPen(QPen(QColor(0xa0, 0xcf, 0xff), 2));
        p.setBrush(Qt::NoBrush);
        QPainterPath focusPath;
        focusPath.addRoundedRect(QRectF(r).adjusted(-1, -1, 1, 1), radius + 1, radius + 1);
        p.drawPath(focusPath);
    }

    // Content
    QColor tc = textColor();
    p.setPen(tc);

    bool hasIcon = !icon().isNull();
    bool hasText = !text().isEmpty();
    int iconSize = s.height - 8;

    if (circle_ && hasIcon) {
        // Circle: icon only, centered
        QIcon::Mode mode = !isEnabled() ? QIcon::Disabled : isDown() ? QIcon::Selected : hovered_ ? QIcon::Active : QIcon::Normal;
        icon().paint(&p, r.center().x() - iconSize/2, r.center().y() - iconSize/2, iconSize, iconSize, Qt::AlignCenter, mode);
    } else {
        // Calculate total content width
        int textW = hasText ? QFontMetrics(f).horizontalAdvance(text()) : 0;
        int totalW = textW;
        if (hasIcon) totalW += iconSize + (hasText ? s.iconGap : 0);

        int startX = r.center().x() - totalW / 2;
        int y = r.center().y();

        if (hasIcon) {
            QIcon::Mode mode = !isEnabled() ? QIcon::Disabled : isDown() ? QIcon::Selected : hovered_ ? QIcon::Active : QIcon::Normal;
            icon().paint(&p, startX, y - iconSize/2, iconSize, iconSize, Qt::AlignCenter, mode);
            startX += iconSize + s.iconGap;
        }

        if (hasText) {
            QFontMetrics fm(f);
            QString elided = fm.elidedText(text(), Qt::ElideRight, textW);
            p.drawText(startX, y - fm.height()/2, textW, fm.height(), Qt::AlignCenter, elided);
        }
    }
}

void ZButton::enterEvent(QEvent*)
{
    hovered_ = true;
    update();
}

void ZButton::leaveEvent(QEvent*)
{
    hovered_ = false;
    update();
}

void ZButton::keyPressEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_Space || e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
        click();
        return;
    }
    QAbstractButton::keyPressEvent(e);
}

void ZButton::changeEvent(QEvent*)
{
    update();
}
