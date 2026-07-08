#include <QHBoxLayout>
#include <QWidget>
#include "widgets/button/zbutton.h"

QWidget* ZButtonDemoLink() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    {
        auto* btn = new ZButton("Primary");
        btn->setButtonType(ZButton::kPrimary);
        btn->setButtonVariant(ZButton::kLink);
        row->addWidget(btn);
    }
    {
        auto* btn = new ZButton("Disabled");
        btn->setButtonType(ZButton::kPrimary);
        btn->setButtonVariant(ZButton::kLink);
        btn->setEnabled(false);
        row->addWidget(btn);
    }
    row->addStretch();
    return w;
}
