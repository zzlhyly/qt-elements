#include <QVBoxLayout>
#include <QWidget>
#include "widgets/progress/zprogress.h"

QWidget* ZProgressDemoStatus() {
    auto* w = new QWidget();
    auto* col = new QVBoxLayout(w);
    col->setSpacing(12);

    auto* success = new ZProgress();
    success->setType(ZProgress::kLine);
    success->setPercentage(100);
    success->setStatus(ZProgress::kSuccess);
    col->addWidget(success);

    auto* exception = new ZProgress();
    exception->setType(ZProgress::kLine);
    exception->setPercentage(50);
    exception->setStatus(ZProgress::kException);
    col->addWidget(exception);

    auto* warningP = new ZProgress();
    warningP->setType(ZProgress::kLine);
    warningP->setPercentage(30);
    warningP->setStatus(ZProgress::kWarning);
    col->addWidget(warningP);

    auto* normal = new ZProgress();
    normal->setType(ZProgress::kLine);
    normal->setPercentage(80);
    normal->setStatus(ZProgress::kNormal);
    col->addWidget(normal);

    return w;
}
