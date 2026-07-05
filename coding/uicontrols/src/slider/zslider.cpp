#include "zslider.h"
#include "theme/theme.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

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
void ZSlider::setValue(int value)
{
    value_ = qBound(min_, value, max_);
    update();
    emit valueChanged(value_);
}

QSize ZSlider::sizeHint() const
{
    return QSize(200, 24);
}

int ZSlider::thumbX() const
{
    int trackW = width() - 2 * trackPad_;
    if (max_ <= min_) return trackPad_;
    double ratio = static_cast<double>(value_ - min_) / (max_ - min_);
    return static_cast<int>(trackPad_ + ratio * trackW);
}

int ZSlider::valueFromX(int x) const
{
    int trackW = width() - 2 * trackPad_;
    if (trackW <= 0) return min_;
    double ratio = static_cast<double>(x - trackPad_) / trackW;
    return qRound(min_ + ratio * (max_ - min_));
}

QRect ZSlider::thumbRect() const
{
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

    // Track background (unfilled)
    QRectF trackRect(trackPad_, ty, w - 2.0 * trackPad_, trackH);
    QPainterPath trackPath;
    trackPath.addRoundedRect(trackRect, 2.0, 2.0);
    p.setBrush(QColor(0xe4, 0xe7, 0xed));
    p.setPen(Qt::NoPen);
    p.drawPath(trackPath);

    // Track filled portion
    int fillEnd = tx;
    QRectF fillRect(trackPad_, ty, fillEnd - trackPad_, trackH);
    if (fillRect.width() > 0) {
        QPainterPath fillPath;
        fillPath.addRoundedRect(fillRect, 2.0, 2.0);
        // Clip to track rect on the right to keep rounded corners clean
        fillPath = fillPath.intersected(trackPath);
        QColor fillColor = disabled ? QColor(0xc0, 0xc4, 0xcc) : theme::colorPrimary();
        p.setBrush(fillColor);
        p.setPen(Qt::NoPen);
        p.drawPath(fillPath);
    }

    // Thumb circle
    int thumbSize = 14;
    int thumbX = tx;
    int thumbY = h / 2;

    QRectF thumbRectF(thumbX - thumbSize / 2.0, thumbY - thumbSize / 2.0,
                      thumbSize, thumbSize);

    QColor thumbBorder = disabled ? QColor(0xc0, 0xc4, 0xcc) : theme::colorPrimary();
    p.setBrush(Qt::white);
    p.setPen(QPen(thumbBorder, 2));
    p.drawEllipse(thumbRectF);
}

void ZSlider::mousePressEvent(QMouseEvent* e)
{
    if (e->button() != Qt::LeftButton) {
        QWidget::mousePressEvent(e);
        return;
    }
    if (!isEnabled()) return;

    QRect tr = thumbRect();
    if (tr.contains(e->pos())) {
        dragging_ = true;
    } else {
        setValue(valueFromX(e->x()));
    }
}

void ZSlider::mouseMoveEvent(QMouseEvent* e)
{
    if (dragging_) {
        setValue(valueFromX(e->x()));
    }
}

void ZSlider::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton && dragging_) {
        dragging_ = false;
        update();
        e->accept();
        return;
    }
    QWidget::mouseReleaseEvent(e);
}
