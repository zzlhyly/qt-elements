#include <QVBoxLayout>
#include <QWidget>
#include "widgets/input/zinput.h"

QWidget* ZInputDemoClearable() {
    auto* w = new QWidget();
    auto* layout = new QVBoxLayout(w);
    layout->setSpacing(12);

    auto* input = new ZInput();
    input->setPlaceholderText("Clearable input");
    input->setClearable(true);
    layout->addWidget(input);

    layout->addStretch();
    return w;
}
