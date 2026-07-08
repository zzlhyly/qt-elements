#include <QHBoxLayout>
#include <QWidget>
#include "widgets/switch/zswitch.h"

QWidget* ZSwitchDemoWithLabel() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* s1 = new ZSwitch();
    s1->setActiveText("ON");
    s1->setInactiveText("OFF");
    row->addWidget(s1);

    auto* s2 = new ZSwitch();
    s2->setActiveText("ON");
    s2->setInactiveText("OFF");
    s2->setChecked(true);
    row->addWidget(s2);

    row->addStretch();
    return w;
}
