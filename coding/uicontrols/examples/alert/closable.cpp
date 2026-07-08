#include <QWidget>
#include "widgets/alert/zalert.h"

QWidget* ZAlertDemoClosable() {
    auto* alert = new ZAlert("Closable alert - click the close button to hide", ZAlert::kInfo);
    alert->setEffect(ZAlert::kLight);
    alert->setClosable(true);
    QObject::connect(alert, &ZAlert::closed, alert, &QWidget::hide);
    return alert;
}
