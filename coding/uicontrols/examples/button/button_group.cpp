#include <QButtonGroup>
#include <QHBoxLayout>
#include <QWidget>
#include "widgets/button/zbutton.h"

QWidget* ZButtonDemoButtonGroup() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);
    auto* group = new QButtonGroup(w);
    auto* btn1 = new ZButton("Left");
    btn1->setButtonType(ZButton::kPrimary);
    btn1->setCheckable(true);
    group->addButton(btn1);
    row->addWidget(btn1);
    auto* btn2 = new ZButton("Center");
    btn2->setButtonType(ZButton::kPrimary);
    btn2->setCheckable(true);
    group->addButton(btn2);
    row->addWidget(btn2);
    auto* btn3 = new ZButton("Right");
    btn3->setButtonType(ZButton::kPrimary);
    btn3->setCheckable(true);
    group->addButton(btn3);
    row->addWidget(btn3);
    row->addStretch();
    return w;
}
