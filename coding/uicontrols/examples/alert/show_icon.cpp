#include <QVBoxLayout>
#include <QWidget>
#include "widgets/alert/zalert.h"

QWidget* ZAlertDemoShowIcon() {
    auto* w = new QWidget();
    auto* col = new QVBoxLayout(w);
    col->setSpacing(12);
    auto* withIcon = new ZAlert("With icon", ZAlert::kInfo);
    withIcon->setEffect(ZAlert::kLight);
    withIcon->setShowIcon(true);
    col->addWidget(withIcon);
    auto* noIcon = new ZAlert("Without icon", ZAlert::kInfo);
    noIcon->setEffect(ZAlert::kLight);
    noIcon->setShowIcon(false);
    col->addWidget(noIcon);
    col->addStretch();
    return w;
}
