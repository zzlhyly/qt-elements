#include "zcheckbox.h"
#include "theme/theme.h"
#include "painter/painter.h"

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

void ZCheckbox::setIndeterminate(bool ind) { indeterminate_ = ind; update(); }

void ZCheckbox::nextCheckState() {
    indeterminate_ = false;
    QAbstractButton::nextCheckState();
}

QSize ZCheckbox::sizeHint() const
{
    QFont f = font();
    f.setPixelSize(14);
    QFontMetrics fm(f);
    int textW = fm.horizontalAdvance(text());
    return QSize(14 + 8 + textW, qMax(20, fm.height()));
}

void ZCheckbox::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    bool checked = isChecked();
    bool disabled = !isEnabled();

    QFont f = font();
    f.setPixelSize(14);
    QFontMetrics fm(f);
    int boxSize = 14;
    int y = (height() - boxSize) / 2;
    QRectF boxRect(0, y, boxSize, boxSize);
    qreal radius = theme::borderRadiusSmall();

    if (indeterminate_) {
        painter::DrawBackground(p, boxRect.toRect(), theme::colorPrimary(), radius);
        // White dash in center — glyph too simple for a Painter function
        p.setBrush(Qt::white);
        p.setPen(Qt::NoPen);
        p.drawRoundedRect(QRectF(boxRect.x() + 3.0, boxRect.y() + 6.0, 8.0, 2.0), 1.0, 1.0);
    } else if (disabled) {
        if (checked) {
            painter::DrawBackground(p, boxRect.toRect(), theme::fillLight(), radius);
            QPen checkPen(theme::textDisabled(), 2);
            checkPen.setCapStyle(Qt::RoundCap);
            p.setPen(checkPen);
            QPainterPath path;
            path.moveTo(boxRect.x() + 4.0, boxRect.y() + 7.5);
            path.lineTo(boxRect.x() + 6.5, boxRect.y() + 10.0);
            path.lineTo(boxRect.x() + 10.5, boxRect.y() + 4.5);
            p.drawPath(path);
        } else {
            painter::DrawBackground(p, boxRect.toRect(), theme::fillLight(), radius);
            painter::DrawBorder(p, boxRect, theme::borderLight(), 1.0, radius);
        }
    } else if (checked) {
        painter::DrawBackground(p, boxRect.toRect(), theme::colorPrimary(), radius);
        QPen checkPen(Qt::white, 2);
        checkPen.setCapStyle(Qt::RoundCap);
        p.setPen(checkPen);
        QPainterPath path;
        path.moveTo(boxRect.x() + 4.0, boxRect.y() + 7.5);
        path.lineTo(boxRect.x() + 6.5, boxRect.y() + 10.0);
        path.lineTo(boxRect.x() + 10.5, boxRect.y() + 4.5);
        p.drawPath(path);
    } else {
        QColor boxPenColor = underMouse() ? theme::colorPrimary() : theme::borderColor();
        painter::DrawBackground(p, boxRect.toRect(), Qt::white, radius);
        painter::DrawBorder(p, boxRect, boxPenColor, 1.0, radius);
    }

    int textX = boxSize + 8;
    QColor textCol = disabled ? theme::textDisabled() : theme::textRegular();
    painter::DrawText(p, QRect(textX, 0, width() - textX, height()),
                      text(), f, textCol, Qt::AlignLeft | Qt::AlignVCenter);
}
