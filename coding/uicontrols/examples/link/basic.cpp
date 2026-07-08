#include <QHBoxLayout>
#include <QWidget>
#include "widgets/link/zlink.h"

QWidget* ZLinkDemoBasic() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    auto* primary = new ZLink("Link");
    primary->setLinkType(ZLink::kPrimary);
    row->addWidget(primary);
    auto* def = new ZLink("Link");
    def->setLinkType(ZLink::kDefault);
    row->addWidget(def);
    row->addStretch();
    return w;
}
