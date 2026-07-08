#include <QHBoxLayout>
#include <QWidget>
#include "widgets/link/zlink.h"

QWidget* ZLinkDemoDisabled() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    auto* link = new ZLink("Disabled");
    link->setLinkType(ZLink::kPrimary);
    link->setEnabled(false);
    row->addWidget(link);
    row->addStretch();
    return w;
}
