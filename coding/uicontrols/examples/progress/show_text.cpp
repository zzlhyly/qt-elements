#include <QVBoxLayout>
#include <QWidget>
#include "widgets/progress/zprogress.h"
#include "progress/progress_demos.h"

QWidget* ZProgressDemoShowText() {
    auto* w = new QWidget();
    auto* layout = new QVBoxLayout(w);
    layout->setSpacing(12);

    auto* with_text = new ZProgress();
    with_text->setPercentage(60);
    with_text->setShowText(true);
    layout->addWidget(with_text);

    auto* without_text = new ZProgress();
    without_text->setPercentage(60);
    without_text->setShowText(false);
    layout->addWidget(without_text);

    layout->addStretch();
    return w;
}
