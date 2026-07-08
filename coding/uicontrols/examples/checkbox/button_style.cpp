#include <QButtonGroup>
#include <QHBoxLayout>
#include <QWidget>
#include "widgets/checkbox/zcheckbox.h"

QWidget* ZCheckboxDemoButtonStyle() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* group = new QButtonGroup(w);

    auto* cb1 = new ZCheckbox("A");
    group->addButton(cb1);
    row->addWidget(cb1);

    auto* cb2 = new ZCheckbox("B");
    group->addButton(cb2);
    row->addWidget(cb2);

    auto* cb3 = new ZCheckbox("C");
    group->addButton(cb3);
    row->addWidget(cb3);

    row->addStretch();
    return w;
}
