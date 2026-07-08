#include <QHBoxLayout>
#include <QWidget>
#include "widgets/slider/zslider.h"

QWidget* ZSliderDemoStops() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    auto* slider = new ZSlider();
    slider->setStep(25);
    slider->setShowStops(true);
    slider->setValue(50);
    row->addWidget(slider);
    return w;
}
