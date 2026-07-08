#include <QHBoxLayout>
#include <QWidget>
#include "widgets/button/zbutton.h"

QWidget* ZButtonDemoDisabled() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    const ZButton::ButtonType types[] = {ZButton::kDefault, ZButton::kPrimary,
                                         ZButton::kSuccess, ZButton::kInfo,
                                         ZButton::kWarning, ZButton::kDanger};
    const char* names[] = {"Default", "Primary", "Success",
                           "Info", "Warning", "Danger"};
    for (int i = 0; i < 6; ++i) {
        auto* btn = new ZButton(names[i]);
        btn->setButtonType(types[i]);
        btn->setEnabled(false);
        row->addWidget(btn);
    }
    row->addStretch();
    return w;
}
