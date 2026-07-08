#include <QHBoxLayout>
#include <QWidget>
#include "widgets/checkbox/zcheckbox.h"

QWidget* ZCheckboxDemoDisabled() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* cb1 = new ZCheckbox("Option 1");
    cb1->setEnabled(false);
    row->addWidget(cb1);

    auto* cb2 = new ZCheckbox("Option 2");
    cb2->setChecked(true);
    cb2->setEnabled(false);
    row->addWidget(cb2);

    row->addStretch();
    return w;
}
