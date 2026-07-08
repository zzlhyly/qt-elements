#include <QVBoxLayout>
#include <QWidget>
#include "widgets/input/zinput.h"

QWidget* ZInputDemoDisabled() {
    auto* w = new QWidget();
    auto* layout = new QVBoxLayout(w);
    layout->setSpacing(12);

    auto* input = new ZInput();
    input->setPlaceholderText("Disabled input");
    input->setEnabled(false);
    layout->addWidget(input);

    layout->addStretch();
    return w;
}
