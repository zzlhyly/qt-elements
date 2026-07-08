#include <QHBoxLayout>
#include <QWidget>
#include "widgets/button/zbutton.h"

QWidget* ZButtonDemoSize() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    const ZButton::ButtonSize sizes[] = {ZButton::kLarge, ZButton::kMedium,
                                         ZButton::kSmall};
    const char* names[] = {"Large", "Medium", "Small"};
    for (int i = 0; i < 3; ++i) {
        auto* btn = new ZButton(names[i]);
        btn->setButtonType(ZButton::kPrimary);
        btn->setButtonSize(sizes[i]);
        row->addWidget(btn);
    }
    row->addStretch();
    return w;
}
