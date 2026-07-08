#include <QButtonGroup>
#include <QHBoxLayout>
#include <QWidget>
#include "widgets/radio/zradio.h"

QWidget* ZRadioDemoBasic() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* group = new QButtonGroup(w);

    auto* r1 = new ZRadio("Option A");
    r1->setChecked(true);
    group->addButton(r1);
    row->addWidget(r1);

    auto* r2 = new ZRadio("Option B");
    group->addButton(r2);
    row->addWidget(r2);

    row->addStretch();
    return w;
}
