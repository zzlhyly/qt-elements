#include "zdivider.h"
#include "theme/theme.h"

#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>

ZDivider::ZDivider(QWidget* parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

ZDivider::ZDivider(const QString& text, QWidget* parent)
    : QWidget(parent)
    , text_(text)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void ZDivider::setText(const QString& text)
{
    text_ = text;
    updateGeometry();
    update();
}

void ZDivider::setDirection(Direction dir)
{
    direction_ = dir;
    if (dir == kVertical) {
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    } else {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }
    updateGeometry();
    update();
}

void ZDivider::setContentPosition(ContentPosition pos)
{
    contentPos_ = pos;
    update();
}

void ZDivider::setBorderStyle(BorderStyle style)
{
    borderStyle_ = style;
    update();
}

QString ZDivider::text() const { return text_; }
ZDivider::Direction ZDivider::direction() const { return direction_; }
ZDivider::ContentPosition ZDivider::contentPosition() const { return contentPos_; }
ZDivider::BorderStyle ZDivider::borderStyle() const { return borderStyle_; }

QSize ZDivider::sizeHint() const
{
    if (direction_ == kVertical) {
        return QSize(1, 200);
    }
    return QSize(200, 20);
}

void ZDivider::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QFont f = font();
    f.setPixelSize(12);
    f.setWeight(QFont::Medium);
    p.setFont(f);

    QColor lineColor = theme::borderColor();
    QColor textColor = theme::textRegular();

    Qt::PenStyle penStyle = Qt::SolidLine;
    if (borderStyle_ == kDashed) penStyle = Qt::DashLine;
    else if (borderStyle_ == kDotted) penStyle = Qt::DotLine;

    QPen linePen(lineColor, 1, penStyle);
    QFontMetrics fm(f);

    if (direction_ == kVertical) {
        // Vertical divider: draw a vertical line centered
        qreal cx = rect().center().x();
        p.setPen(linePen);
        p.drawLine(QPointF(cx, 0), QPointF(cx, height()));
        return;
    }

    // Horizontal divider
    if (text_.isEmpty()) {
        // Full-width line at vertical center
        p.setPen(linePen);
        qreal cy = rect().center().y();
        p.drawLine(QPointF(0, cy), QPointF(width(), cy));
        return;
    }

    // Horizontal divider with text
    int textW = fm.horizontalAdvance(text_);
    int textH = fm.height();
    qreal cy = rect().center().y();
    int gap = 20;  // gap between text and line on each side

    // Text position
    int textX = 0;
    if (contentPos_ == kLeft) {
        textX = 0;
    } else if (contentPos_ == kRight) {
        textX = width() - textW;
    } else {
        textX = (width() - textW) / 2;
    }

    // Clip text area so lines don't draw through text
    QRect textRect(textX, static_cast<int>(cy - textH / 2.0), textW, textH);

    // Left line segment
    p.setPen(linePen);
    if (contentPos_ == kLeft) {
        // Line to the right of text only
        p.drawLine(QPointF(textRect.right() + gap, cy), QPointF(width(), cy));
    } else if (contentPos_ == kRight) {
        // Line to the left of text only
        p.drawLine(QPointF(0, cy), QPointF(textRect.left() - gap, cy));
    } else {
        // Both sides
        p.drawLine(QPointF(0, cy), QPointF(textRect.left() - gap, cy));
        p.drawLine(QPointF(textRect.right() + gap, cy), QPointF(width(), cy));
    }

    // Draw text
    p.setPen(textColor);
    p.drawText(textRect, Qt::AlignCenter, text_);
}
