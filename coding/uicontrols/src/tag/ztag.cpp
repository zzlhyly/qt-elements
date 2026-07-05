#include "ztag.h"

#include <QFontMetrics>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

// Color tables: [TagType][effect] - 0=normal bg, 1=text color, 2=border color
// Light: type-specific light bg + type-color text, no border
// Dark: type-color bg + white text, no border
// Plain: white bg + type-color text + type-color border

// Color tables indexed by [TagType]: kPrimary=0, kSuccess=1, kInfo=2, kWarning=3, kDanger=4
// Element Plus Tag SCSS: genTheme('light-9','light-8','') for light; genTheme(false,'light-5','') for plain

static const QColor tagBgLight[5] = {
    {0xec, 0xf5, 0xff},  // primary-light-9
    {0xf0, 0xf9, 0xeb},  // success-light-9
    {0xf4, 0xf4, 0xf5},  // info-light-9
    {0xfd, 0xf6, 0xec},  // warning-light-9
    {0xfe, 0xf0, 0xf0},  // danger-light-9
};

static const QColor tagBorderLight[5] = {
    {0xd9, 0xec, 0xff},  // primary-light-8
    {0xe1, 0xf3, 0xd8},  // success-light-8
    {0xe9, 0xe9, 0xeb},  // info-light-8
    {0xfa, 0xec, 0xd8},  // warning-light-8
    {0xfd, 0xe2, 0xe2},  // danger-light-8
};

static const QColor tagBorderPlain[5] = {
    {0xa0, 0xcf, 0xff},  // primary-light-5
    {0xb3, 0xe1, 0x9d},  // success-light-5
    {0xc8, 0xc9, 0xcc},  // info-light-5
    {0xf3, 0xd1, 0x9e},  // warning-light-5
    {0xfa, 0xb6, 0xb6},  // danger-light-5
};

static const QColor tagTextLight[5] = {
    {0x40, 0x9e, 0xff},  // primary: blue
    {0x67, 0xc2, 0x3a},  // success: green
    {0x90, 0x93, 0x99},  // info: grey
    {0xe6, 0xa2, 0x3c},  // warning: orange
    {0xf5, 0x6c, 0x6c},  // danger: red
};

static const QColor tagBgDark[5] = {
    {0x40, 0x9e, 0xff},  // primary: blue
    {0x67, 0xc2, 0x3a},  // success: green
    {0x90, 0x93, 0x99},  // info: grey
    {0xe6, 0xa2, 0x3c},  // warning: orange
    {0xf5, 0x6c, 0x6c},  // danger: red
};

// Tag color tables: ordered [kPrimary, kSuccess, kInfo, kWarning, kDanger]
// This matches Element Plus where Tag types use their corresponding colors

ZTag::ZTag(QWidget* parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

ZTag::ZTag(const QString& text, QWidget* parent)
    : QWidget(parent)
    , text_(text)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

void ZTag::setText(const QString& text)
{
    text_ = text;
    updateGeometry();
    update();
}

QString ZTag::text() const
{
    return text_;
}

void ZTag::setTagType(TagType type)  { type_ = type; update(); }
void ZTag::setEffect(TagEffect e)    { effect_ = e; update(); }
void ZTag::setTagSize(TagSize s)     { size_ = s; updateGeometry(); update(); }
void ZTag::setClosable(bool c)       { closable_ = c; update(); }
void ZTag::setRound(bool r)          { round_ = r; update(); }
void ZTag::setHit(bool h)            { hit_ = h; update(); }

ZTag::TagType ZTag::tagType() const   { return type_; }
ZTag::TagEffect ZTag::effect() const  { return effect_; }
ZTag::TagSize ZTag::tagSize() const   { return size_; }
bool ZTag::isClosable() const         { return closable_; }
bool ZTag::isRound() const            { return round_; }
bool ZTag::isHit() const              { return hit_; }

const ZTag::SizeSpec& ZTag::sizeSpec() const
{
    // Element Plus Tag sizes: large=32, default/medium=28, small=24
    static const SizeSpec specs[] = {
        { 32, 12, 4, 8, 12, 6 },  // Large
        { 28, 12, 4, 8, 10, 6 },  // Medium
        { 24, 11, 3, 7, 8,  4 },  // Small
    };
    return specs[size_];
}

QColor ZTag::bgColor() const
{
    if (effect_ == kDark) return tagBgDark[type_];
    if (effect_ == kPlain) return Qt::white;
    // kLight
    return tagBgLight[type_];
}

QColor ZTag::textColor() const
{
    if (effect_ == kDark) return Qt::white;
    // kLight and kPlain use same text colors
    return tagTextLight[type_];
}

QColor ZTag::borderColor() const
{
    if (effect_ == kPlain) return tagBorderPlain[type_];
    if (effect_ == kLight) return tagBorderLight[type_];
    if (hit_) return tagTextLight[type_];
    return Qt::transparent;
}

QRect ZTag::closeButtonRect() const
{
    if (!closable_) return QRect();
    const SizeSpec& s = sizeSpec();
    int cs = s.closeSize;
    int cm = s.closeMargin;
    return QRect(width() - cm - cs, (height() - cs) / 2, cs, cs);
}

QSize ZTag::sizeHint() const
{
    const SizeSpec& s = sizeSpec();
    QFont f = font();
    f.setPixelSize(s.fontSize);
    f.setWeight(QFont::Medium);
    QFontMetrics fm(f);

    int w = s.padH * 2 + fm.horizontalAdvance(text());
    if (closable_) w += s.closeSize + s.closeMargin;
    w = qMax(w, s.height * 2);  // min width ~ 2x height
    return QSize(w, s.height);
}

QSize ZTag::minimumSizeHint() const
{
    return QSize(0, sizeSpec().height);
}

void ZTag::paintEvent(QPaintEvent*)
{
    const SizeSpec& s = sizeSpec();
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QFont f = font();
    f.setPixelSize(s.fontSize);
    f.setWeight(QFont::Medium);
    p.setFont(f);

    QRect r = rect();
    qreal radius = round_ ? 20.0 : s.radius;

    // Background
    QPainterPath path;
    path.addRoundedRect(QRectF(r), radius, radius);
    p.setBrush(bgColor());
    p.setPen(Qt::NoPen);
    p.drawPath(path);

    // Border (plain or hit mode)
    QColor bc = borderColor();
    if (bc != Qt::transparent) {
        p.setBrush(Qt::NoBrush);
        p.setPen(QPen(bc, 1));
        p.drawPath(path);
    }

    // Text — centered in available space (excluding close button area)
    p.setPen(textColor());
    QFontMetrics fm(f);
    QRect textRect = r;
    if (closable_) {
        textRect.setRight(r.right() - s.closeSize - s.closeMargin);
    }

    int availableW = textRect.width() - s.padH * 2;
    QString displayText = fm.elidedText(text(), Qt::ElideRight, availableW);
    p.drawText(textRect, Qt::AlignCenter, displayText);

    // Close button
    if (closable_) {
        QRect cb = closeButtonRect();
        QColor closeColor = textColor();
        if (close_pressed_) {
            closeColor = closeColor.darker(120);
        } else if (close_hovered_) {
            closeColor = textColor();  // same, but could lighten
        }

        // Draw close icon with slightly smaller font
        QFont cf = font();
        cf.setPixelSize(s.fontSize + 2);
        cf.setWeight(QFont::Normal);
        p.setFont(cf);
        p.setPen(closeColor);
        p.drawText(cb, Qt::AlignCenter, QString(QChar(0x00D7)));
    }
}

void ZTag::mousePressEvent(QMouseEvent* e)
{
    if (closable_ && closeButtonRect().contains(e->pos())) {
        close_pressed_ = true;
        update();
        e->accept();
        return;
    }
    QWidget::mousePressEvent(e);
}

void ZTag::mouseReleaseEvent(QMouseEvent* e)
{
    if (close_pressed_ && closable_ && closeButtonRect().contains(e->pos())) {
        close_pressed_ = false;
        close_hovered_ = false;
        emit closed();
        update();
        e->accept();
        return;
    }
    close_pressed_ = false;
    update();
    QWidget::mouseReleaseEvent(e);
}

void ZTag::mouseMoveEvent(QMouseEvent* e)
{
    if (closable_) {
        bool wasHovered = close_hovered_;
        close_hovered_ = closeButtonRect().contains(e->pos());
        if (close_hovered_ != wasHovered) update();
    }
    QWidget::mouseMoveEvent(e);
}
