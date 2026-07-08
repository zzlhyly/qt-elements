#include <QHBoxLayout>
#include <QWidget>
#include "widgets/button/zbutton.h"

QWidget* ZButtonDemoPlain() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    const ZButton::ButtonType types[] = {ZButton::kPrimary, ZButton::kSuccess,
                                         ZButton::kInfo, ZButton::kWarning,
                                         ZButton::kDanger};
    const char* names[] = {"Primary", "Success", "Info", "Warning", "Danger"};
    for (int i = 0; i < 5; ++i) {
        auto* btn = new ZButton(names[i]);
        btn->setButtonType(types[i]);
        btn->setButtonVariant(ZButton::kPlain);
        row->addWidget(btn);
    }
    row->addStretch();
    return w;
}
