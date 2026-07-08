#include <QVBoxLayout>
#include <QWidget>
#include "widgets/alert/zalert.h"

QWidget* ZAlertDemoBasic() {
    auto* w = new QWidget();
    auto* col = new QVBoxLayout(w);
    col->setSpacing(12);
    const char* names[] = {"Success alert", "Info alert", "Warning alert", "Error alert"};
    const ZAlert::AlertType types[] = {ZAlert::kSuccess, ZAlert::kInfo,
                                       ZAlert::kWarning, ZAlert::kError};
    for (int i = 0; i < 4; ++i) {
        auto* alert = new ZAlert(names[i], types[i]);
        alert->setEffect(ZAlert::kLight);
        col->addWidget(alert);
    }
    col->addStretch();
    return w;
}
