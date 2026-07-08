#include "zdivider.h"
#include "painter/painter.h"

#include <QFontMetrics>
#include <QPainter>

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

void ZDivider::setText(const QString& text)          { text_ = text; updateGeometry(); update(); }
void ZDivider::setDirection(Direction dir) {
    direction_ = dir;
    if (dir == kVertical) setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    else setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    updateGeometry(); update();
}
void ZDivider::setContentPosition(ContentPosition p) { contentPos_ = p; update(); }
void ZDivider::setBorderStyle(BorderStyle s)          { borderStyle_ = s; update(); }

QString ZDivider::text() const                       { return text_; }
ZDivider::Direction ZDivider::direction() const       { return direction_; }
ZDivider::ContentPosition ZDivider::contentPosition() const { return contentPos_; }
ZDivider::BorderStyle ZDivider::borderStyle() const   { return borderStyle_; }

QSize ZDivider::sizeHint() const
{
    if (direction_ == kVertical) return QSize(1, 200);
    return QSize(200, 20);
}

void ZDivider::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QColor lineColor = theme::borderColor();
    Qt::PenStyle penStyle = Qt::SolidLine;
    if (borderStyle_ == kDashed) penStyle = Qt::DashLine;
    else if (borderStyle_ == kDotted) penStyle = Qt::DotLine;

    if (direction_ == kVertical) {
        qreal cx = rect().center().x();
        p.setPen(QPen(lineColor, 1, penStyle));
        p.drawLine(QPointF(cx, 0), QPointF(cx, height()));
        return;
    }

    // Horizontal: full line if no text
    if (text_.isEmpty()) {
        qreal cy = rect().center().y();
        p.setPen(QPen(lineColor, 1, penStyle));
        p.drawLine(QPointF(0, cy), QPointF(width(), cy));
        return;
    }

    // Horizontal with text
    QFont f = font();
    f.setPixelSize(12);
    f.setWeight(QFont::Medium);
    QFontMetrics fm(f);
    int textW = fm.horizontalAdvance(text_);
    qreal cy = rect().center().y();
    int gap = 20;

    int textX = 0;
    if (contentPos_ == kLeft) textX = 0;
    else if (contentPos_ == kRight) textX = width() - textW;
    else textX = (width() - textW) / 2;

    p.setPen(QPen(lineColor, 1, penStyle));
    if (contentPos_ == kLeft) {
        p.drawLine(QPointF(textX + textW + gap, cy), QPointF(width(), cy));
    } else if (contentPos_ == kRight) {
        p.drawLine(QPointF(0, cy), QPointF(textX - gap, cy));
    } else {
        p.drawLine(QPointF(0, cy), QPointF(textX - gap, cy));
        p.drawLine(QPointF(textX + textW + gap, cy), QPointF(width(), cy));
    }

    painter::DrawText(p, QRect(textX, 0, textW, height()), text_, f,
                      theme::textRegular(), Qt::AlignCenter);
}
