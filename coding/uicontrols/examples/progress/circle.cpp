#include <QHBoxLayout>
#include <QWidget>
#include "widgets/progress/zprogress.h"

QWidget* ZProgressDemoCircle() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    auto* prog = new ZProgress();
    prog->setType(ZProgress::kCircle);
    prog->setPercentage(75);
    prog->setFixedSize(126, 126);
    row->addWidget(prog);
    return w;
}
