#include "testwidget.h"
#include "button/zbutton.h"
#include <QPushButton>
#include <QVBoxLayout>

TestWidget::TestWidget(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(30);

    ZButton* btn = new ZButton(this);
    btn->setButtonSize(ZButton::BS_Large);
    layout->addWidget(btn);

    ZButton* btn1 = new ZButton(this);
    btn1->setButtonSize(ZButton::BS_Medium);
    layout->addWidget(btn1);

    ZButton* btn2 = new ZButton(this);
    btn2->setButtonSize(ZButton::BS_Small);
    layout->addWidget(btn2);

    ZButton* btn3 = new ZButton(this);
    btn3->setButtonSize(ZButton::BS_Small);
    btn3->setButtonType(ZButton::BT_Chips);
    layout->addWidget(btn3);

    ZButton* btn4 = new ZButton(this);
    btn4->setButtonSize(ZButton::BS_Medium);
    btn4->setButtonType(ZButton::BT_Chips);
    layout->addWidget(btn4);

    ZButton* btn5 = new ZButton(this);
    btn5->setButtonSize(ZButton::BS_Large);
    btn5->setButtonType(ZButton::BT_Chips);
    layout->addWidget(btn5);

}
