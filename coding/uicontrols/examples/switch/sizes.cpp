#include <QHBoxLayout>
#include <QWidget>
#include "widgets/switch/zswitch.h"

QWidget* ZSwitchDemoSizes() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* s1 = new ZSwitch();
    s1->setSwitchSize(ZSwitch::kLarge);
    row->addWidget(s1);

    auto* s2 = new ZSwitch();
    s2->setSwitchSize(ZSwitch::kDefault);
    row->addWidget(s2);

    auto* s3 = new ZSwitch();
    s3->setSwitchSize(ZSwitch::kSmall);
    row->addWidget(s3);

    row->addStretch();
    return w;
}
