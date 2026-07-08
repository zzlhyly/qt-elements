#include <QVBoxLayout>
#include <QWidget>
#include "widgets/alert/zalert.h"

QWidget* ZAlertDemoCenter() {
    auto* w = new QWidget();
    auto* col = new QVBoxLayout(w);
    col->setSpacing(12);
    auto* centered = new ZAlert("Centered alert", ZAlert::kInfo);
    centered->setEffect(ZAlert::kLight);
    centered->setCenter(true);
    col->addWidget(centered);
    auto* left = new ZAlert("Left-aligned alert", ZAlert::kInfo);
    left->setEffect(ZAlert::kLight);
    left->setCenter(false);
    col->addWidget(left);
    col->addStretch();
    return w;
}
