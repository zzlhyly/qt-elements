#include "zslider.h"
#include "theme/theme.h"
#include "painter/painter.h"

#include <QMouseEvent>
#include <QPainter>

ZSlider::ZSlider(QWidget* parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setMinimumHeight(24);
    setCursor(Qt::PointingHandCursor);
    setMouseTracking(true);
}

void ZSlider::setMinimum(int min) { min_ = min; if (value_ < min_) setValue(min_); update(); }
void ZSlider::setMaximum(int max) { max_ = max; if (value_ > max_) setValue(max_); update(); }
void ZSlider::setValue(int v)     { value_ = qBound(min_, v, max_); update(); emit valueChanged(value_); }
void ZSlider::setStep(int step)   { step_ = qMax(1, step); update(); }
void ZSlider::setShowStops(bool s) { showStops_ = s; update(); }

QSize ZSlider::sizeHint() const   { return QSize(200, 24); }

int ZSlider::thumbX() const {
    int trackW = width() - 2 * trackPad_;
    if (max_ <= min_) return trackPad_;
    double ratio = static_cast<double>(value_ - min_) / (max_ - min_);
    return static_cast<int>(trackPad_ + ratio * trackW);
}

int ZSlider::valueFromX(int x) const {
    int trackW = width() - 2 * trackPad_;
    if (trackW <= 0) return min_;
    double ratio = static_cast<double>(x - trackPad_) / trackW;
    int raw = qRound(min_ + ratio * (max_ - min_));
    if (step_ > 1) raw = qRound(static_cast<double>(raw - min_) / step_) * step_ + min_;
    return qBound(min_, raw, max_);
}

QRect ZSlider::thumbRect() const {
    int thumbSize = 14;
    int tx = thumbX() - thumbSize / 2;
    int ty = (height() - thumbSize) / 2;
    return QRect(tx, ty, thumbSize, thumbSize);
}

void ZSlider::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    int w = width();
    int h = height();
    int trackH = 4;
    int ty = (h - trackH) / 2;
    bool disabled = !isEnabled();
    int tx = thumbX();

    // Track background
    painter::DrawBackground(p, QRect(trackPad_, ty, w - 2 * trackPad_, trackH),
                            QColor(0xe4, 0xe7, 0xed), 2.0);

    // Filled portion
    int fillEnd = tx;
    QRect fillRect(trackPad_, ty, fillEnd - trackPad_, trackH);
    if (fillRect.width() > 0) {
        QColor fillColor = disabled ? QColor(0xc0, 0xc4, 0xcc) : theme::colorPrimary();
        painter::DrawBackground(p, QRect(trackPad_, ty, fillEnd - trackPad_, trackH),
                                fillColor, 2.0);
    }

    // Stops
    if (showStops_ && !disabled && max_ > min_) {
        int stopCount = (max_ - min_) / step_ + 1;
        int trackW = w - 2 * trackPad_;
        p.setBrush(Qt::white);
        p.setPen(QPen(QColor(0xdc, 0xdf, 0xe6), 1));
        for (int i = 0; i < stopCount; ++i) {
            int stopVal = min_ + i * step_;
            double r = static_cast<double>(stopVal - min_) / (max_ - min_);
            int sx = static_cast<int>(trackPad_ + r * trackW);
            p.drawEllipse(QPointF(sx, ty + trackH / 2.0), 2.0, 2.0);
        }
    }

    // Thumb
    int thumbSize = 14;
    QColor thumbBorder = disabled ? QColor(0xc0, 0xc4, 0xcc) : theme::colorPrimary();
    painter::DrawBackground(p, QRect(tx - thumbSize / 2, h / 2 - thumbSize / 2, thumbSize, thumbSize),
                            Qt::white, thumbSize / 2.0);
    p.setPen(QPen(thumbBorder, 2));
    p.setBrush(Qt::NoBrush);
    p.drawEllipse(QPointF(tx, h / 2.0), thumbSize / 2.0, thumbSize / 2.0);
}

void ZSlider::mousePressEvent(QMouseEvent* e) {
    if (e->button() != Qt::LeftButton || !isEnabled()) return;
    if (thumbRect().contains(e->pos())) dragging_ = true;
    else setValue(valueFromX(e->x()));
}

void ZSlider::mouseMoveEvent(QMouseEvent* e) {
    if (dragging_) setValue(valueFromX(e->x()));
}

void ZSlider::mouseReleaseEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton && dragging_) { dragging_ = false; update(); }
    else QWidget::mouseReleaseEvent(e);
}
