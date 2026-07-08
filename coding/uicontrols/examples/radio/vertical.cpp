#include <QButtonGroup>
#include <QVBoxLayout>
#include <QWidget>
#include "widgets/radio/zradio.h"

QWidget* ZRadioDemoVertical() {
    auto* w = new QWidget();
    auto* col = new QVBoxLayout(w);
    col->setSpacing(12);

    auto* group = new QButtonGroup(w);

    const char* labels[] = {"Option A", "Option B", "Option C", "Option D"};
    for (int i = 0; i < 4; ++i) {
        auto* r = new ZRadio(labels[i]);
        group->addButton(r);
        col->addWidget(r);
    }

    col->addStretch();
    return w;
}
