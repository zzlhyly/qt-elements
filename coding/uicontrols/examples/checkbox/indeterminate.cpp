#include <QVBoxLayout>
#include <QWidget>
#include "widgets/checkbox/zcheckbox.h"

QWidget* ZCheckboxDemoIndeterminate() {
    auto* w = new QWidget();
    auto* col = new QVBoxLayout(w);
    col->setSpacing(12);

    auto* select_all = new ZCheckbox("Select all");
    select_all->setIndeterminate(true);
    col->addWidget(select_all);

    auto* opt1 = new ZCheckbox("Option A");
    col->addWidget(opt1);

    auto* opt2 = new ZCheckbox("Option B");
    col->addWidget(opt2);

    col->addStretch();
    return w;
}
