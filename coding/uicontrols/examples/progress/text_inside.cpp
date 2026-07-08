#include <QHBoxLayout>
#include <QWidget>
#include "widgets/progress/zprogress.h"

QWidget* ZProgressDemoTextInside() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    auto* prog = new ZProgress();
    prog->setType(ZProgress::kLine);
    prog->setPercentage(50);
    prog->setTextInside(true);
    row->addWidget(prog);
    return w;
}
