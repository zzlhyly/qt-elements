#include <QHBoxLayout>
#include <QWidget>
#include "widgets/checkbox/zcheckbox.h"

QWidget* ZCheckboxDemoBasic() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* cb1 = new ZCheckbox("Option 1");
    row->addWidget(cb1);

    auto* cb2 = new ZCheckbox("Option 2");
    cb2->setChecked(true);
    row->addWidget(cb2);

    auto* cb3 = new ZCheckbox("Option 3");
    cb3->setChecked(true);
    row->addWidget(cb3);

    row->addStretch();
    return w;
}
