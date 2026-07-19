#include "zslider.h"
#include "theme/theme.h"
#include "painter/painter.h"

#include <QMouseEvent>
#include <QPainter>

ZSlider::ZSlider(QWidget* parent) : QWidget(parent) {
    setMouseTracking(true);
    setCursor(Qt::PointingHandCursor);
    if (direction_ == kHorizontal) { setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); setMinimumHeight(24); }
    else { setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding); setMinimumWidth(24); }
}

void ZSlider::setMinimum(int m) { min_ = m; if (value_ < m) setValue(m); update(); }
void ZSlider::setMaximum(int m) { max_ = m; if (value_ > m) setValue(m); update(); }
void ZSlider::setValue(int v)   { value_ = qBound(min_, v, max_); update(); emit valueChanged(value_); }
void ZSlider::setStep(int s)    { step_ = qMax(1, s); update(); }
void ZSlider::setShowStops(bool s) { showStops_ = s; update(); }

void ZSlider::setDirection(Direction dir) {
    direction_ = dir;
    if (dir == kHorizontal) { setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); setMinimumHeight(24); setMaximumHeight(16777215); }
    else { setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding); setMinimumWidth(24); setMaximumWidth(16777215); }
    updateGeometry(); update();
}

QSize ZSlider::sizeHint() const {
    if (direction_ == kHorizontal) return QSize(200, 24);
    return QSize(24, 200);
}

int ZSlider::thumbPos() const {
    int trackLen = (direction_ == kHorizontal ? width() : height()) - 2 * trackPad_;
    if (max_ <= min_) return trackPad_;
    double ratio = static_cast<double>(value_ - min_) / (max_ - min_);
    return static_cast<int>(trackPad_ + ratio * trackLen);
}

int ZSlider::valueFromPos(int pos) const {
    int trackLen = (direction_ == kHorizontal ? width() : height()) - 2 * trackPad_;
    if (trackLen <= 0) return min_;
    double ratio = static_cast<double>(pos - trackPad_) / trackLen;
    int raw = qRound(min_ + ratio * (max_ - min_));
    if (step_ > 1) raw = qRound(static_cast<double>(raw - min_) / step_) * step_ + min_;
    return qBound(min_, raw, max_);
}

QRect ZSlider::thumbRect() const {
    int thumbSize = 14;
    int tp = thumbPos();
    if (direction_ == kHorizontal) return QRect(tp - thumbSize / 2, (height() - thumbSize) / 2, thumbSize, thumbSize);
    return QRect((width() - thumbSize) / 2, tp - thumbSize / 2, thumbSize, thumbSize);
}

void ZSlider::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    bool disabled = !isEnabled();
    int tp = thumbPos();

    if (direction_ == kHorizontal) {
        int w = width(), h = height(), trackH = 4, ty = (h - trackH) / 2;
        painter::DrawBackground(p, QRect(trackPad_, ty, w - 2 * trackPad_, trackH), QColor(0xe4, 0xe7, 0xed), 2.0);
        if (tp - trackPad_ > 0) {
            QColor fill = disabled ? QColor(0xc0, 0xc4, 0xcc) : theme::colorPrimary();
            painter::DrawBackground(p, QRect(trackPad_, ty, tp - trackPad_, trackH), fill, 2.0);
        }
        if (showStops_ && !disabled && max_ > min_) {
            int trackW = w - 2 * trackPad_;
            p.setBrush(Qt::white); p.setPen(QPen(QColor(0xdc, 0xdf, 0xe6), 1));
            for (int v = min_; v <= max_; v += step_) {
                double r = static_cast<double>(v - min_) / (max_ - min_);
                p.drawEllipse(QPointF(trackPad_ + r * trackW, ty + trackH / 2.0), 2.0, 2.0);
            }
        }
        int thumbSize = 14;
        painter::DrawBackground(p, QRect(tp - thumbSize / 2, h / 2 - thumbSize / 2, thumbSize, thumbSize), Qt::white, thumbSize / 2.0);
        p.setPen(QPen(disabled ? QColor(0xc0, 0xc4, 0xcc) : theme::colorPrimary(), 2));
        p.setBrush(Qt::NoBrush);
        p.drawEllipse(QPointF(tp, h / 2.0), thumbSize / 2.0, thumbSize / 2.0);
    } else {
        int w = width(), h = height(), trackW = 4, tx = (w - trackW) / 2;
        painter::DrawBackground(p, QRect(tx, trackPad_, trackW, h - 2 * trackPad_), QColor(0xe4, 0xe7, 0xed), 2.0);
        int fillEnd = h - tp;
        if (fillEnd > 0) {
            QColor fill = disabled ? QColor(0xc0, 0xc4, 0xcc) : theme::colorPrimary();
            painter::DrawBackground(p, QRect(tx, tp, trackW, fillEnd), fill, 2.0);
        }
        int thumbSize = 14;
        painter::DrawBackground(p, QRect(w / 2 - thumbSize / 2, tp - thumbSize / 2, thumbSize, thumbSize), Qt::white, thumbSize / 2.0);
        p.setPen(QPen(disabled ? QColor(0xc0, 0xc4, 0xcc) : theme::colorPrimary(), 2));
        p.setBrush(Qt::NoBrush);
        p.drawEllipse(QPointF(w / 2.0, tp), thumbSize / 2.0, thumbSize / 2.0);
    }
}

static int posFromEvent(const QMouseEvent* e, bool horiz) {
    return horiz ? e->x() : e->y();
}

void ZSlider::mousePressEvent(QMouseEvent* e) {
    if (e->button() != Qt::LeftButton || !isEnabled()) return;
    bool horiz = (direction_ == kHorizontal);
    if (thumbRect().contains(e->pos())) dragging_ = true;
    else setValue(valueFromPos(posFromEvent(e, horiz)));
}
void ZSlider::mouseMoveEvent(QMouseEvent* e) {
    bool horiz = (direction_ == kHorizontal);
    if (dragging_) setValue(valueFromPos(posFromEvent(e, horiz)));
}
void ZSlider::mouseReleaseEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton && dragging_) { dragging_ = false; update(); }
    else QWidget::mouseReleaseEvent(e);
}
