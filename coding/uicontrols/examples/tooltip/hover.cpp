#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "widgets/tooltip/ztooltip.h"

QWidget* ZTooltipDemoHover() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* btn1 = new QPushButton("Dark tooltip");
    ZTooltip::install(btn1, "This is a dark tooltip", ZPopup::kTop, ZTooltip::kDark);
    row->addWidget(btn1);

    auto* btn2 = new QPushButton("Light tooltip");
    ZTooltip::install(btn2, "This is a light tooltip", ZPopup::kTop, ZTooltip::kLight);
    row->addWidget(btn2);

    return w;
}
