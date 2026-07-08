#include <QHBoxLayout>
#include <QWidget>
#include "widgets/alert/zalert.h"

QWidget* ZAlertDemoTheme() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    auto* light = new ZAlert("Light alert", ZAlert::kInfo);
    light->setEffect(ZAlert::kLight);
    row->addWidget(light);
    auto* dark = new ZAlert("Dark alert", ZAlert::kInfo);
    dark->setEffect(ZAlert::kDark);
    row->addWidget(dark);
    row->addStretch();
    return w;
}
