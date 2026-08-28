#include <QHBoxLayout>
#include <QWidget>
#include "widgets/progress/zprogress.h"
#include "progress/progress_demos.h"

QWidget* ZProgressDemoStrokeWidth() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(16);

    const int widths[] = {3, 6, 12};
    for (int width : widths) {
        auto* prog = new ZProgress();
        prog->setPercentage(50);
        prog->setStrokeWidth(width);
        row->addWidget(prog);
    }

    row->addStretch();
    return w;
}
