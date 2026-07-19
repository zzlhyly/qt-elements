#include <QVBoxLayout>
#include <QWidget>
#include "widgets/input/zinput.h"

QWidget* ZInputDemoAutosize() {
    auto* w = new QWidget();
    auto* layout = new QVBoxLayout(w);
    layout->setSpacing(12);

    auto* input = new ZInput();
    input->setTextarea(3);
    input->setAutosize(true);
    input->setAutosizeMinRows(2);
    input->setAutosizeMaxRows(6);
    input->setText("Line 1\nLine 2\nLine 3\nLine 4\nLine 5");
    layout->addWidget(input);

    layout->addStretch();
    return w;
}
