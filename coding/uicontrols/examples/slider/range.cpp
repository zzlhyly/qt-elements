#include <QHBoxLayout>
#include <QWidget>
#include "widgets/slider/zslider.h"
#include "slider/slider_demos.h"

QWidget* ZSliderDemoRange() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    auto* slider = new ZSlider();
    slider->setMinimum(20);
    slider->setMaximum(80);
    slider->setValue(50);
    row->addWidget(slider);
    return w;
}
