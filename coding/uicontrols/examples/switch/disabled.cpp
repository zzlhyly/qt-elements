#include <QHBoxLayout>
#include <QWidget>
#include "widgets/switch/zswitch.h"

QWidget* ZSwitchDemoDisabled() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* s1 = new ZSwitch();
    s1->setEnabled(false);
    row->addWidget(s1);

    auto* s2 = new ZSwitch();
    s2->setChecked(true);
    s2->setEnabled(false);
    row->addWidget(s2);

    row->addStretch();
    return w;
}
