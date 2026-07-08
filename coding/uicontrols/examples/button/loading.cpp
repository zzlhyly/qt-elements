#include <QHBoxLayout>
#include <QWidget>
#include "widgets/button/zbutton.h"

QWidget* ZButtonDemoLoading() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    {
        auto* btn = new ZButton("Loading");
        btn->setButtonType(ZButton::kPrimary);
        btn->setLoading(true);
        row->addWidget(btn);
    }
    {
        auto* btn = new ZButton("Loading");
        btn->setButtonType(ZButton::kPrimary);
        btn->setButtonSize(ZButton::kMedium);
        btn->setLoading(true);
        row->addWidget(btn);
    }
    {
        auto* btn = new ZButton("Loading");
        btn->setButtonType(ZButton::kPrimary);
        btn->setButtonSize(ZButton::kSmall);
        btn->setLoading(true);
        row->addWidget(btn);
    }
    row->addStretch();
    return w;
}
