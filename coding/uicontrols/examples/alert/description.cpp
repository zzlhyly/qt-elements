#include <QWidget>
#include "widgets/alert/zalert.h"
#include "alert/alert_demos.h"

QWidget* ZAlertDemoDescription() {
    auto* alert = new ZAlert(
        "This is a detailed description of the alert message",
        ZAlert::kError);
    alert->setEffect(ZAlert::kLight);
    return alert;
}
