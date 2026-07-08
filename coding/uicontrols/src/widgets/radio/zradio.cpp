#include "zradio.h"
#include "theme/theme.h"
#include "painter/painter.h"

#include <QFontMetrics>
#include <QPainter>

ZRadio::ZRadio(QWidget* parent)
    : QAbstractButton(parent)
{
    setCheckable(true);
    setCursor(Qt::PointingHandCursor);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

ZRadio::ZRadio(const QString& text, QWidget* parent)
    : QAbstractButton(parent)
{
    setText(text);
    setCheckable(true);
    setCursor(Qt::PointingHandCursor);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

QSize ZRadio::sizeHint() const
{
    QFont f = font();
    f.setPixelSize(14);
    QFontMetrics fm(f);
    int textW = fm.horizontalAdvance(text());
    int totalH = qMax(border_ ? 28 : 20, fm.height() + (border_ ? 8 : 0));
    return QSize(14 + 8 + textW, totalH);
}

void ZRadio::setBorder(bool border) { border_ = border; update(); }

void ZRadio::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    bool checked = isChecked();
    bool disabled = !isEnabled();

    QFont f = font();
    f.setPixelSize(14);

    int circleSize = 14;
    int y = (height() - circleSize) / 2;

    if (border_) {
        QColor borderClr = checked ? theme::colorPrimary() : theme::borderColor();
        painter::DrawBorder(p, rect().adjusted(0, 0, -1, -1), borderClr, 1.0, 4.0);
    }

    QRectF circleRect(0, y, circleSize, circleSize);
    QColor outerColor;
    if (disabled) outerColor = theme::borderLight();
    else if (checked || underMouse()) outerColor = theme::colorPrimary();
    else outerColor = theme::borderColor();

    // Outer circle
    painter::DrawBackground(p, circleRect.toRect(), Qt::white, circleSize / 2.0);
    painter::DrawBorder(p, circleRect, outerColor, 1.0, circleSize / 2.0);

    if (checked) {
        QColor dotColor = disabled ? theme::textDisabled() : theme::colorPrimary();
        QRectF dotRect = circleRect.adjusted(4, 4, -4, -4);
        painter::DrawBackground(p, dotRect.toRect(), dotColor, 3.0);
    }

    int textX = circleSize + 8;
    QColor textColor = disabled ? theme::textDisabled() : theme::textRegular();
    painter::DrawText(p, QRect(textX, 0, width() - textX, height()),
                      text(), f, textColor, Qt::AlignLeft | Qt::AlignVCenter);
}
