#include <QHBoxLayout>
#include <QWidget>
#include "widgets/link/zlink.h"

QWidget* ZLinkDemoTypes() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    const char* names[] = {"Default", "Primary", "Success", "Warning", "Danger", "Info"};
    const ZLink::LinkType types[] = {ZLink::kDefault, ZLink::kPrimary, ZLink::kSuccess,
                                     ZLink::kWarning, ZLink::kDanger, ZLink::kInfo};
    for (int i = 0; i < 6; ++i) {
        auto* link = new ZLink(names[i]);
        link->setLinkType(types[i]);
        row->addWidget(link);
    }
    row->addStretch();
    return w;
}
