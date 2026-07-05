#include "zswitch.h"
#include "theme/theme.h"

#include <QPainter>
#include <QPainterPath>

ZSwitch::ZSwitch(QWidget* parent)
    : QAbstractButton(parent)
{
    setCheckable(true);
    setCursor(Qt::PointingHandCursor);
    setFixedSize(40, 20);

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
    setChecked(!isChecked());
    anim_->setStartValue(offset_);
    anim_->setEndValue(isChecked() ? 1.0 : 0.0);
    anim_->start();
}

void ZSwitch::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    bool checked = isChecked();
    bool disabled = !isEnabled();

    const qreal trackW = 40.0;
    const qreal trackH = 20.0;
    const qreal trackRadius = trackH / 2.0;  // 10
    const qreal thumbD = 16.0;
    const qreal thumbR = thumbD / 2.0;       // 8
    const qreal margin = 2.0;  // gap between thumb and track edge

    // Track
    QRectF trackRect(0, 0, trackW, trackH);
    QPainterPath trackPath;
    trackPath.addRoundedRect(trackRect, trackRadius, trackRadius);

    QColor trackColor;
    if (disabled) {
        trackColor = QColor(0xe0, 0xe0, 0xe0);
    } else if (checked) {
        trackColor = theme::colorPrimary();
    } else {
        trackColor = QColor(0xc0, 0xc4, 0xcc);
    }
    p.setBrush(trackColor);
    p.setPen(Qt::NoPen);
    p.drawPath(trackPath);

    // Thumb position: travels from margin to trackW - margin - thumbD
    qreal thumbTravel = trackW - 2.0 * margin - thumbD;  // 40 - 4 - 16 = 20
    qreal thumbX = margin + offset_ * thumbTravel;
    qreal thumbY = (trackH - thumbD) / 2.0;

    QRectF thumbRect(thumbX, thumbY, thumbD, thumbD);

    // Thumb shadow (subtle, offset down-right)
    QRectF shadowRect = thumbRect.translated(0.5, 0.5);
    p.setBrush(QColor(0, 0, 0, 30));
    p.setPen(Qt::NoPen);
    p.drawEllipse(shadowRect);

    // Thumb
    p.setBrush(disabled ? QColor(0xf5, 0xf5, 0xf5) : Qt::white);
    p.drawEllipse(thumbRect);
}
