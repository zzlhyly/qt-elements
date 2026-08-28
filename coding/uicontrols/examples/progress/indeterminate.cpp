#include <QHBoxLayout>
#include <QWidget>
#include "widgets/progress/zprogress.h"
#include "progress/progress_demos.h"

QWidget* ZProgressDemoIndeterminate() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    auto* prog = new ZProgress();
    prog->setType(ZProgress::kLine);
    prog->setIndeterminate(true);
    row->addWidget(prog);
    return w;
}
