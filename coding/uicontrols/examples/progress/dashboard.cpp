#include <QHBoxLayout>
#include <QWidget>
#include "widgets/progress/zprogress.h"

QWidget* ZProgressDemoDashboard() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    auto* prog = new ZProgress();
    prog->setType(ZProgress::kDashboard);
    prog->setPercentage(60);
    prog->setFixedSize(126, 126);
    row->addWidget(prog);
    return w;
}
