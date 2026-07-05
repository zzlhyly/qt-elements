#include "zcheckbox.h"
#include "theme/theme.h"

#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>

ZCheckbox::ZCheckbox(QWidget* parent)
    : QAbstractButton(parent)
{
    setCheckable(true);
    setCursor(Qt::PointingHandCursor);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

ZCheckbox::ZCheckbox(const QString& text, QWidget* parent)
    : QAbstractButton(parent)
{
    setText(text);
    setCheckable(true);
    setCursor(Qt::PointingHandCursor);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

QSize ZCheckbox::sizeHint() const
{
    QFont f = font();
    f.setPixelSize(14);
    f.setWeight(QFont::Normal);
    QFontMetrics fm(f);
    int textW = fm.horizontalAdvance(text());
    int totalW = 14 + 8 + textW;  // box + gap + text
    return QSize(totalW, qMax(20, fm.height()));
}

void ZCheckbox::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    bool checked = isChecked();
    bool disabled = !isEnabled();

    QFont f = font();
    f.setPixelSize(14);
    f.setWeight(QFont::Normal);
    p.setFont(f);

    QFontMetrics fm(f);
    int boxSize = 14;
    int y = (height() - boxSize) / 2;
    QRectF boxRect(0, y, boxSize, boxSize);
    qreal radius = theme::borderRadiusSmall(); // 2px

    if (disabled) {
        if (checked) {
            // Disabled checked: light bg with disabled checkmark
            p.setBrush(theme::fillLight());
            p.setPen(Qt::NoPen);
            p.drawRoundedRect(boxRect, radius, radius);
            QPen checkPen(theme::textDisabled(), 2);
            checkPen.setCapStyle(Qt::RoundCap);
            p.setPen(checkPen);
            QPainterPath path;
            path.moveTo(boxRect.x() + 4.0, boxRect.y() + 7.5);
            path.lineTo(boxRect.x() + 6.5, boxRect.y() + 10.0);
            path.lineTo(boxRect.x() + 10.5, boxRect.y() + 4.5);
            p.drawPath(path);
        } else {
            p.setBrush(theme::fillLight());
            p.setPen(QPen(theme::borderLight(), 1));
            p.drawRoundedRect(boxRect, radius, radius);
        }
    } else if (checked) {
        // Checked: primary fill + white checkmark
        p.setBrush(theme::colorPrimary());
        p.setPen(Qt::NoPen);
        p.drawRoundedRect(boxRect, radius, radius);
        QPen checkPen(Qt::white, 2);
        checkPen.setCapStyle(Qt::RoundCap);
        p.setPen(checkPen);
        QPainterPath path;
        path.moveTo(boxRect.x() + 4.0, boxRect.y() + 7.5);
        path.lineTo(boxRect.x() + 6.5, boxRect.y() + 10.0);
        path.lineTo(boxRect.x() + 10.5, boxRect.y() + 4.5);
        p.drawPath(path);
    } else {
        // Unchecked
        QColor boxPenColor = underMouse() ? theme::colorPrimary() : theme::borderColor();
        p.setBrush(Qt::white);
        p.setPen(QPen(boxPenColor, 1));
        p.drawRoundedRect(boxRect, radius, radius);
    }

    // Text
    int textX = boxSize + 8;
    QColor textCol = disabled ? theme::textDisabled() : theme::textRegular();
    p.setPen(textCol);
    QRect textRect(textX, 0, width() - textX, height());
    p.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text());
}
