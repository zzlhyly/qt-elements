#ifndef CODING_UICONTROLS_SRC_SLIDER_ZSLIDER_H_
#define CODING_UICONTROLS_SRC_SLIDER_ZSLIDER_H_

#include <QWidget>

class ZSlider : public QWidget
{
    Q_OBJECT

public:
    explicit ZSlider(QWidget* parent = nullptr);

    void setMinimum(int min);
    void setMaximum(int max);
    void setValue(int value);
    void setStep(int step);
    void setShowStops(bool show);

    int minimum() const { return min_; }
    int maximum() const { return max_; }
    int value() const { return value_; }
    int step() const { return step_; }
    bool isShowStops() const { return showStops_; }

    QSize sizeHint() const override;

signals:
    void valueChanged(int value);

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private:
    int thumbX() const;
    int valueFromX(int x) const;
    QRect thumbRect() const;

    int min_ = 0;
    int max_ = 100;
    int value_ = 0;
    int step_ = 1;
    bool showStops_ = false;
    bool dragging_ = false;
    int trackPad_ = 10;
};

#endif // CODING_UICONTROLS_SRC_SLIDER_ZSLIDER_H_
