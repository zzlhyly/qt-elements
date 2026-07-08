#include <QHBoxLayout>
#include <QWidget>
#include "widgets/switch/zswitch.h"

QWidget* ZSwitchDemoBasic() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* s1 = new ZSwitch();
    row->addWidget(s1);

    auto* s2 = new ZSwitch();
    s2->setChecked(true);
    row->addWidget(s2);

    row->addStretch();
    return w;
}
