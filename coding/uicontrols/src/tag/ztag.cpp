#include "ztag.h"
#include "theme/theme.h"

#include <QFontMetrics>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

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

theme::SizeSpec ZTag::sizeSpec() const
{
    return theme::tagSize(size_);
}

QColor ZTag::bgColor() const
{
    if (effect_ == kDark) return theme::tagDarkBg(static_cast<int>(type_));
    if (effect_ == kPlain) return Qt::white;
    return theme::tagLightBg(static_cast<int>(type_));
}

QColor ZTag::textColor() const
{
    if (effect_ == kDark) return Qt::white;
    return theme::tagTextColor(static_cast<int>(type_));
}

QColor ZTag::borderColor() const
{
    if (effect_ == kPlain) return theme::tagPlainBorder(static_cast<int>(type_));
    if (effect_ == kLight) return theme::tagLightBorder(static_cast<int>(type_));
    if (hit_) return theme::tagTextColor(static_cast<int>(type_));
    return Qt::transparent;
}

QRect ZTag::closeButtonRect() const
{
    if (!closable_) return QRect();
    const theme::SizeSpec& s = sizeSpec();
    int cs = theme::tagCloseSize(size_);
    int cm = s.iconGap;
    return QRect(width() - cm - cs, (height() - cs) / 2, cs, cs);
}

QSize ZTag::sizeHint() const
{
    const theme::SizeSpec& s = sizeSpec();
    QFont f = font();
    f.setPixelSize(s.fontSize);
    f.setWeight(QFont::Medium);
    QFontMetrics fm(f);

    int w = s.padH * 2 + fm.horizontalAdvance(text());
    if (closable_) w += theme::tagCloseSize(size_) + s.iconGap;
    w = qMax(w, s.height * 2);  // min width ~ 2x height
    return QSize(w, s.height);
}

QSize ZTag::minimumSizeHint() const
{
    return QSize(0, sizeSpec().height);
}

void ZTag::paintEvent(QPaintEvent*)
{
    const theme::SizeSpec& s = sizeSpec();
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
        textRect.setRight(r.right() - theme::tagCloseSize(size_) - s.iconGap);
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
