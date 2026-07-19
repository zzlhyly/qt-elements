#ifndef WIDGETS_SLIDER_ZSLIDER_H_
#define WIDGETS_SLIDER_ZSLIDER_H_

#include <QWidget>

// ZSlider — Element Plus slider component.
// Supports horizontal/vertical orientation, step snapping, stop markers,
// and drag interaction. Renders track, fill, and thumb via QPainter.

class ZSlider : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int value READ value WRITE setValue)
    Q_PROPERTY(int step READ step WRITE setStep)
    Q_PROPERTY(bool showStops READ isShowStops WRITE setShowStops)
    Q_PROPERTY(Direction direction READ direction WRITE setDirection)

public:
    enum Direction { kHorizontal, kVertical };

    explicit ZSlider(QWidget* parent = nullptr);

    void setMinimum(int min);
    void setMaximum(int max);
    void setValue(int value);
    void setStep(int step);
    void setShowStops(bool show);
    void setDirection(Direction dir);

    int minimum() const { return min_; }
    int maximum() const { return max_; }
    int value() const { return value_; }
    int step() const { return step_; }
    bool isShowStops() const { return showStops_; }
    Direction direction() const { return direction_; }

    QSize sizeHint() const override;

signals:
    void valueChanged(int value);

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private:
    int thumbPos() const;
    int valueFromPos(int pos) const;
    QRect thumbRect() const;

    int min_ = 0;
    int max_ = 100;
    int value_ = 0;
    int step_ = 1;
    bool showStops_ = false;
    bool dragging_ = false;
    int trackPad_ = 10;
    Direction direction_ = kHorizontal;
};

#endif // WIDGETS_SLIDER_ZSLIDER_H_
