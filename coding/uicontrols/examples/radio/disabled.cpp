#include <QHBoxLayout>
#include <QWidget>
#include "widgets/radio/zradio.h"

QWidget* ZRadioDemoDisabled() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    auto* r1 = new ZRadio("Option A");
    r1->setChecked(true);
    r1->setEnabled(false);
    row->addWidget(r1);

    auto* r2 = new ZRadio("Option B");
    r2->setEnabled(false);
    row->addWidget(r2);

    row->addStretch();
    return w;
}
