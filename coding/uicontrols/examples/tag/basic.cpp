#include <QHBoxLayout>
#include <QWidget>
#include "widgets/tag/ztag.h"

QWidget* ZTagDemoBasic() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    const char* names[] = {"Primary", "Success", "Info", "Warning", "Danger"};
    const ZTag::TagType types[] = {ZTag::kPrimary, ZTag::kSuccess, ZTag::kInfo,
                                   ZTag::kWarning, ZTag::kDanger};
    for (int i = 0; i < 5; ++i) {
        auto* tag = new ZTag(names[i]);
        tag->setTagType(types[i]);
        tag->setEffect(ZTag::kLight);
        row->addWidget(tag);
    }
    row->addStretch();
    return w;
}
