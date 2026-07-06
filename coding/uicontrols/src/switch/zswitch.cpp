#include "zswitch.h"
#include "theme/theme.h"

#include <QPainter>
#include <QPainterPath>
#include <QTimer>

ZSwitch::ZSwitch(QWidget* parent)
    : QAbstractButton(parent)
{
    setCheckable(true);
    setCursor(Qt::PointingHandCursor);
    setFixedSize(40, 20);

    anim_ = new QPropertyAnimation(this, "offset", this);
    anim_->setDuration(200);
    anim_->setEasingCurve(QEasingCurve::InOutCubic);

    loading_timer_ = new QTimer(this);
    loading_timer_->setInterval(50);
    connect(loading_timer_, &QTimer::timeout, this, [this]() {
        loading_angle_ = (loading_angle_ + 30) % 360;
        update();
    });
}

QSize ZSwitch::sizeHint() const
{
    switch (size_) {
    case kLarge: return QSize(48, 24);
    case kSmall: return QSize(32, 16);
    default:     return QSize(40, 20);
    }
}

void ZSwitch::setOffset(qreal o)
{
    offset_ = o;
    update();
}

void ZSwitch::setSwitchSize(SwitchSize size)
{
    size_ = size;
    switch (size) {
    case kLarge: setFixedSize(48, 24); break;
    case kSmall: setFixedSize(32, 16); break;
    default:     setFixedSize(40, 20); break;
    }
    updateGeometry();
    update();
}

void ZSwitch::setLoading(bool loading)
{
    loading_ = loading;
    if (loading) {
        loading_timer_->start();
    } else {
        loading_timer_->stop();
    }
    setEnabled(!loading);
    update();
}

void ZSwitch::setActiveText(const QString& text)
{
    active_text_ = text;
    updateGeometry();
    update();
}

void ZSwitch::setInactiveText(const QString& text)
{
    inactive_text_ = text;
    updateGeometry();
    update();
}

void ZSwitch::nextCheckState()
{
    if (loading_) return;
    setChecked(!isChecked());
    anim_->stop();
    anim_->setStartValue(offset_);
    anim_->setEndValue(isChecked() ? 1.0 : 0.0);
    anim_->start();
}

void ZSwitch::checkStateSet()
{
    anim_->stop();
    offset_ = isChecked() ? 1.0 : 0.0;
    update();
    QAbstractButton::checkStateSet();
}

void ZSwitch::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    bool checked = isChecked();
    bool disabled = !isEnabled();

    qreal trackW, trackH, thumbD, margin;
    switch (size_) {
    case kLarge: trackW = 48; trackH = 24; thumbD = 20; margin = 2.0; break;
    case kSmall: trackW = 32; trackH = 16; thumbD = 12; margin = 2.0; break;
    default:     trackW = 40; trackH = 20; thumbD = 16; margin = 2.0; break;
    }
    const qreal trackRadius = trackH / 2.0;

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

    qreal thumbTravel = trackW - 2.0 * margin - thumbD;
    qreal thumbX = margin + offset_ * thumbTravel;
    qreal thumbY = (trackH - thumbD) / 2.0;

    QRectF thumbRect(thumbX, thumbY, thumbD, thumbD);

    if (loading_) {
        // Spinner arc in thumb center
        p.setBrush(Qt::NoBrush);
        QPen spinnerPen(theme::colorPrimary(), 2);
        spinnerPen.setCapStyle(Qt::RoundCap);
        p.setPen(spinnerPen);
        qreal cx = thumbRect.center().x();
        qreal cy = thumbRect.center().y();
        qreal r = 5.0;
        int startAngle = loading_angle_ * 16;
        int spanAngle = 60 * 16;
        p.drawArc(QRectF(cx - r, cy - r, r * 2, r * 2), startAngle, spanAngle);
    } else {
        // Thumb shadow
        QRectF shadowRect = thumbRect.translated(0.5, 0.5);
        p.setBrush(QColor(0, 0, 0, 30));
        p.setPen(Qt::NoPen);
        p.drawEllipse(shadowRect);

        // Thumb
        p.setBrush(disabled ? QColor(0xf5, 0xf5, 0xf5) : Qt::white);
        p.drawEllipse(thumbRect);
    }

    // Active/Inactive text
    QFont tf = p.font();
    tf.setPixelSize(12);
    p.setFont(tf);
    if (checked && !active_text_.isEmpty()) {
        p.setPen(QColor(0x60, 0x62, 0x66));
        QRectF textRect(trackW + 6, 0, width() - trackW - 6, trackH);
        p.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, active_text_);
    } else if (!checked && !inactive_text_.isEmpty()) {
        p.setPen(QColor(0x60, 0x62, 0x66));
        QRectF textRect(trackW + 6, 0, width() - trackW - 6, trackH);
        p.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, inactive_text_);
    }
}
