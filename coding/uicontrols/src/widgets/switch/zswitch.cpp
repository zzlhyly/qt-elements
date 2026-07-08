#include "zswitch.h"
#include "theme/theme.h"
#include "painter/painter.h"

#include <QPainter>
#include <QPainterPath>

ZSwitch::ZSwitch(QWidget* parent)
    : QAbstractButton(parent)
    , anim_manager_(new AnimationManager(this))
{
    setCheckable(true);
    setCursor(Qt::PointingHandCursor);
    setFixedSize(40, 20);
}

QSize ZSwitch::sizeHint() const
{
    switch (size_) {
    case kLarge: return QSize(48, 24);
    case kSmall: return QSize(32, 16);
    default:     return QSize(40, 20);
    }
}

void ZSwitch::setSwitchSize(SwitchSize size) {
    size_ = size;
    switch (size) {
    case kLarge: setFixedSize(48, 24); break;
    case kSmall: setFixedSize(32, 16); break;
    default:     setFixedSize(40, 20); break;
    }
    updateGeometry(); update();
}

void ZSwitch::setLoading(bool loading) {
    loading_ = loading;
    if (loading) startLoadingAnimation();
    else stopLoadingAnimation();
    setEnabled(!loading);
    update();
}

void ZSwitch::setActiveText(const QString& text)  { active_text_ = text; updateGeometry(); update(); }
void ZSwitch::setInactiveText(const QString& text){ inactive_text_ = text; updateGeometry(); update(); }

void ZSwitch::nextCheckState() {
    if (loading_) return;
    setChecked(!isChecked());
    startSlideAnimation();
}

void ZSwitch::checkStateSet() {
    if (slide_anim_.IsValid()) slide_anim_.Stop();
    offset_ = isChecked() ? 1.0 : 0.0;
    update();
    QAbstractButton::checkStateSet();
}

void ZSwitch::startSlideAnimation() {
    // ponytail: CreateProgressAnimation loops infinitely, but slide needs one-shot.
    // Use QVariantAnimation directly; wrap with AnimHandle for lifecycle management.
    // Revisit when AnimationManager supports loopCount parameter.
    if (slide_anim_.IsValid()) slide_anim_.Stop();
    qreal from = offset_;
    qreal to = isChecked() ? 1.0 : 0.0;

    auto* anim = new QVariantAnimation(this);
    anim->setStartValue(from);
    anim->setEndValue(to);
    anim->setDuration(200);
    anim->setEasingCurve(QEasingCurve::InOutCubic);
    anim->setLoopCount(1);
    connect(anim, &QVariantAnimation::valueChanged, this, [this](const QVariant& v) {
        offset_ = v.toReal();
        update();
    });
    anim->start(QAbstractAnimation::DeleteWhenStopped);
    slide_anim_ = AnimHandle(anim);
}

void ZSwitch::startLoadingAnimation() {
    loading_anim_ = anim_manager_->CreateProgressAnimation(this, QByteArray(),
        1000, [this](qreal value) {
            loading_angle_ = value;
            update();
        });
}

void ZSwitch::stopLoadingAnimation() {
    if (loading_anim_.IsValid()) loading_anim_.Stop();
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
    qreal trackRadius = trackH / 2.0;

    // Track background
    QColor trackColor;
    if (disabled) trackColor = QColor(0xe0, 0xe0, 0xe0);
    else if (checked) trackColor = theme::colorPrimary();
    else trackColor = QColor(0xc0, 0xc4, 0xcc);
    painter::DrawBackground(p, QRect(0, 0, static_cast<int>(trackW), static_cast<int>(trackH)),
                            trackColor, trackRadius);

    qreal thumbTravel = trackW - 2.0 * margin - thumbD;
    qreal thumbX = margin + offset_ * thumbTravel;
    qreal thumbY = (trackH - thumbD) / 2.0;

    QRectF thumbRect(thumbX, thumbY, thumbD, thumbD);

    if (loading_) {
        QPen spinnerPen(theme::colorPrimary(), 2);
        spinnerPen.setCapStyle(Qt::RoundCap);
        p.setPen(spinnerPen);
        p.setBrush(Qt::NoBrush);
        qreal cx = thumbRect.center().x();
        qreal cy = thumbRect.center().y();
        qreal r = 5.0;
        p.drawArc(QRectF(cx - r, cy - r, r * 2, r * 2),
                  static_cast<int>(loading_angle_) * 16, 60 * 16);
    } else {
        // Thumb shadow
        painter::DrawBackground(p, thumbRect.translated(0.5, 0.5).toRect(),
                                QColor(0, 0, 0, 30), thumbD / 2.0);
        // Thumb
        painter::DrawBackground(p, thumbRect.toRect(),
                                disabled ? QColor(0xf5, 0xf5, 0xf5) : Qt::white, thumbD / 2.0);
    }

    // Label text
    QFont tf = p.font();
    tf.setPixelSize(12);
    QString label = checked ? active_text_ : inactive_text_;
    if (!label.isEmpty()) {
        QRectF textRect(static_cast<int>(trackW) + 6, 0,
                        width() - static_cast<int>(trackW) - 6, static_cast<int>(trackH));
        painter::DrawText(p, textRect.toRect(), label, tf, QColor(0x60, 0x62, 0x66),
                          Qt::AlignLeft | Qt::AlignVCenter);
    }
}
