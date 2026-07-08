#include <QVBoxLayout>
#include <QWidget>
#include "widgets/divider/zdivider.h"

QWidget* ZDividerDemoWithText() {
    auto* w = new QWidget();
    auto* col = new QVBoxLayout(w);
    col->setSpacing(12);
    auto* d1 = new ZDivider("Center text");
    d1->setContentPosition(ZDivider::kCenter);
    col->addWidget(d1);
    auto* d2 = new ZDivider("Left text");
    d2->setContentPosition(ZDivider::kLeft);
    col->addWidget(d2);
    auto* d3 = new ZDivider("Right text");
    d3->setContentPosition(ZDivider::kRight);
    col->addWidget(d3);
    col->addStretch();
    return w;
}
