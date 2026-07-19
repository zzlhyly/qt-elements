#include <QHBoxLayout>
#include <QWidget>
#include "widgets/slider/zslider.h"

QWidget* ZSliderDemoVertical() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    auto* slider = new ZSlider();
    slider->setDirection(ZSlider::kVertical);
    slider->setMinimumHeight(200);
    slider->setValue(30);
    row->addWidget(slider);
    row->addStretch();
    return w;
}
