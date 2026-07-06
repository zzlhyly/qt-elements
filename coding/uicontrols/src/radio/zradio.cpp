#include "zradio.h"
#include "theme/theme.h"

#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>

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
    f.setWeight(QFont::Normal);
    QFontMetrics fm(f);
    int textW = fm.horizontalAdvance(text());
    int totalW = 14 + 8 + textW;
    int totalH = qMax(border_ ? 28 : 20, fm.height() + (border_ ? 8 : 0));
    return QSize(totalW, totalH);
}

void ZRadio::setBorder(bool border)
{
    border_ = border;
    update();
}

void ZRadio::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    bool checked = isChecked();
    bool disabled = !isEnabled();

    // Font for text
    QFont f = font();
    f.setPixelSize(14);
    f.setWeight(QFont::Normal);
    p.setFont(f);

    QFontMetrics fm(f);
    int circleSize = 14;
    int y = (height() - circleSize) / 2;

    // Border rect
    if (border_) {
        QColor borderClr = checked ? theme::colorPrimary() : QColor(0xdc, 0xdf, 0xe6);
        p.setPen(QPen(borderClr, 1));
        p.setBrush(Qt::white);
        QRectF br = rect().adjusted(0, 0, -1, -1);
        p.drawRoundedRect(br.adjusted(4, 4, -4, -4), 4, 4);
    }

    // Outer circle
    QRectF circleRect(0, y, circleSize, circleSize);
    QColor outerColor;
    if (disabled) {
        outerColor = theme::borderLight();
    } else if (checked || underMouse()) {
        outerColor = theme::colorPrimary();
    } else {
        outerColor = theme::borderColor();
    }

    p.setPen(QPen(outerColor, 1));
    p.setBrush(Qt::white);
    p.drawEllipse(circleRect);

    // Inner dot when checked
    if (checked) {
        QColor dotColor = disabled ? theme::textDisabled() : theme::colorPrimary();
        p.setBrush(dotColor);
        p.setPen(Qt::NoPen);
        p.drawEllipse(circleRect.adjusted(4, 4, -4, -4));  // 6px dot
    }

    // Text
    int textX = circleSize + 8;
    QColor textColor = disabled ? theme::textDisabled() : theme::textRegular();
    p.setPen(textColor);
    QRect textRect(textX, 0, width() - textX, height());
    p.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text());
}
