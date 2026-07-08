#include <QHBoxLayout>
#include <QWidget>
#include "widgets/slider/zslider.h"

QWidget* ZSliderDemoDisabled() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    auto* slider = new ZSlider();
    slider->setValue(30);
    slider->setEnabled(false);
    row->addWidget(slider);
    return w;
}
