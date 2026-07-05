#include "zswitch.h"
#include "theme/theme.h"

#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>

ZSwitch::ZSwitch(QWidget* parent)
    : QAbstractButton(parent)
{
    setCheckable(true);
    setCursor(Qt::PointingHandCursor);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    anim_ = new QPropertyAnimation(this, "offset", this);
    anim_->setDuration(200);
    anim_->setEasingCurve(QEasingCurve::InOutCubic);
}

QSize ZSwitch::sizeHint() const
{
    return QSize(40, 20);
}

void ZSwitch::setOffset(qreal o)
{
    offset_ = o;
    update();
}

void ZSwitch::nextCheckState()
{
    // Toggle check state manually rather than calling base (which would emit toggled)
    setChecked(!isChecked());
    anim_->setStartValue(offset_);
    anim_->setEndValue(isChecked() ? 1.0 : 0.0);
    anim_->start();
}

void ZSwitch::resizeEvent(QResizeEvent* e)
{
    QAbstractButton::resizeEvent(e);
}

void ZSwitch::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    bool checked = isChecked();
    bool disabled = !isEnabled();

    qreal w = 40.0;
    qreal h = 20.0;
    qreal trackRadius = h / 2.0;
    qreal thumbRadius = 8.0;

    // Center the track in the widget rect
    qreal trackH = 20.0;
    qreal trackW = 40.0;
    qreal ty = (height() - trackH) / 2.0;
    qreal tx = (width() - trackW) / 2.0;

    // Track color
    QColor trackColor;
    if (disabled) {
        trackColor = QColor(0xe0, 0xe0, 0xe0);
    } else if (checked) {
        trackColor = theme::colorPrimary();  // #409eff
    } else {
        trackColor = QColor(0xc0, 0xc4, 0xcc);
    }

    // Draw track
    QRectF trackRect(tx, ty, trackW, trackH);
    QPainterPath trackPath;
    trackPath.addRoundedRect(trackRect, trackRadius, trackRadius);
    p.setBrush(trackColor);
    p.setPen(Qt::NoPen);
    p.drawPath(trackPath);

    // Thumb shadow
    qreal thumbX = tx + 2.0 + offset_ * (trackW - 4.0 - thumbRadius * 2.0);
    qreal thumbY = ty + trackH / 2.0;
    QRectF shadowRect(thumbX - thumbRadius + 1, thumbY - thumbRadius + 1,
                      thumbRadius * 2.0, thumbRadius * 2.0);
    QColor shadowColor(0, 0, 0, 15);
    p.setBrush(shadowColor);
    p.setPen(Qt::NoPen);
    p.drawEllipse(shadowRect);

    // Thumb
    QRectF thumbRect(thumbX - thumbRadius, thumbY - thumbRadius,
                     thumbRadius * 2.0, thumbRadius * 2.0);
    p.setBrush(Qt::white);
    p.setPen(Qt::NoPen);
    p.drawEllipse(thumbRect);
}
