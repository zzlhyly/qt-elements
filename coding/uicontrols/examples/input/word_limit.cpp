#include <QVBoxLayout>
#include <QWidget>
#include "widgets/input/zinput.h"

QWidget* ZInputDemoWordLimit() {
    auto* w = new QWidget();
    auto* layout = new QVBoxLayout(w);
    layout->setSpacing(12);

    auto* input = new ZInput();
    input->setTextarea(3);
    input->setShowWordLimit(true);
    input->setMaxLength(100);
    input->setText("Some initial text content for the textarea with word limit.");
    layout->addWidget(input);

    layout->addStretch();
    return w;
}
