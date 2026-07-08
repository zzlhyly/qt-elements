#include <QVBoxLayout>
#include <QWidget>
#include "widgets/tag/ztag.h"

QWidget* ZTagDemoSizes() {
    auto* w = new QWidget();
    auto* col = new QVBoxLayout(w);
    col->setSpacing(12);
    const char* names[] = {"Large", "Medium", "Small"};
    const ZTag::TagSize sizes[] = {ZTag::kLarge, ZTag::kMedium, ZTag::kSmall};
    for (int i = 0; i < 3; ++i) {
        auto* tag = new ZTag(names[i]);
        tag->setTagType(ZTag::kPrimary);
        tag->setEffect(ZTag::kLight);
        tag->setTagSize(sizes[i]);
        col->addWidget(tag);
    }
    col->addStretch();
    return w;
}
