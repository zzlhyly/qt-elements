#include <QHBoxLayout>
#include <QWidget>
#include "widgets/button/zbutton.h"

QWidget* ZButtonDemoCircle() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    const ZButton::ButtonType types[] = {ZButton::kPrimary, ZButton::kSuccess,
                                         ZButton::kInfo, ZButton::kWarning,
                                         ZButton::kDanger};
    const char* labels[] = {"P", "S", "I", "W", "D"};
    for (int i = 0; i < 5; ++i) {
        auto* btn = new ZButton(labels[i]);
        btn->setButtonType(types[i]);
        btn->setCircle(true);
        row->addWidget(btn);
    }
    row->addStretch();
    return w;
}
