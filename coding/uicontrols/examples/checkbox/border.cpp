#include <QVBoxLayout>
#include <QWidget>
#include "widgets/checkboxgroup/zcheckboxgroup.h"
#include "widgets/checkbox/zcheckbox.h"

QWidget* ZCheckboxDemoBorder() {
    auto* w = new QWidget();
    auto* layout = new QVBoxLayout(w);
    layout->setSpacing(12);

    auto* group = new ZCheckboxGroup();
    group->setBorder(true);
    group->setType(ZCheckboxGroup::GroupType::kButton);
    group->addCheckbox(new ZCheckbox("Shanghai"), 1);
    group->addCheckbox(new ZCheckbox("Beijing"), 2);
    group->addCheckbox(new ZCheckbox("Guangzhou"), 3);

    layout->addWidget(group);
    layout->addStretch();
    return w;
}
