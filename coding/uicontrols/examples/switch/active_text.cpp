#include <QHBoxLayout>
#include <QWidget>
#include "widgets/switch/zswitch.h"
#include "switch/switch_demos.h"

QWidget* ZSwitchDemoActiveText() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* off = new ZSwitch();
    off->setActiveText("ON");
    off->setInactiveText("OFF");
    row->addWidget(off);

    auto* on = new ZSwitch();
    on->setChecked(true);
    on->setActiveText("Yes");
    on->setInactiveText("No");
    row->addWidget(on);

    row->addStretch();
    return w;
}
