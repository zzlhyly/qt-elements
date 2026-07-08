#include <QHBoxLayout>
#include <QWidget>
#include "widgets/link/zlink.h"

QWidget* ZLinkDemoUnderline() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    auto* primary = new ZLink("With Underline");
    primary->setLinkType(ZLink::kPrimary);
    primary->setUnderline(true);
    row->addWidget(primary);
    auto* def = new ZLink("With Underline");
    def->setLinkType(ZLink::kDefault);
    def->setUnderline(true);
    row->addWidget(def);
    row->addStretch();
    return w;
}
