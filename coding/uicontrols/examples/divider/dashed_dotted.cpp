#include <QVBoxLayout>
#include <QWidget>
#include "widgets/divider/zdivider.h"

QWidget* ZDividerDemoDashedDotted() {
    auto* w = new QWidget();
    auto* col = new QVBoxLayout(w);
    col->setSpacing(12);
    auto* d1 = new ZDivider("Dashed");
    d1->setBorderStyle(ZDivider::kDashed);
    col->addWidget(d1);
    auto* d2 = new ZDivider("Dotted");
    d2->setBorderStyle(ZDivider::kDotted);
    col->addWidget(d2);
    col->addStretch();
    return w;
}
