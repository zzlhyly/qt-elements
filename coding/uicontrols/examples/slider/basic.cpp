#include <QHBoxLayout>
#include <QWidget>
#include "widgets/slider/zslider.h"
#include "slider/slider_demos.h"

QWidget* ZSliderDemoBasic() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    auto* slider = new ZSlider();
    row->addWidget(slider);
    return w;
}
