#include <QHBoxLayout>
#include <QWidget>
#include "widgets/switch/zswitch.h"

QWidget* ZSwitchDemoLoading() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* s = new ZSwitch();
    s->setLoading(true);
    row->addWidget(s);

    row->addStretch();
    return w;
}
