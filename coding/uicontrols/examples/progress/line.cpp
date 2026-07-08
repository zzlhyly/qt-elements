#include <QHBoxLayout>
#include <QWidget>
#include "widgets/progress/zprogress.h"

QWidget* ZProgressDemoLine() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    auto* prog = new ZProgress();
    prog->setPercentage(50);
    prog->setStrokeWidth(8);
    row->addWidget(prog);
    return w;
}
