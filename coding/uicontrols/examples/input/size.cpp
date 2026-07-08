#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include "widgets/input/zinput.h"

QWidget* ZInputDemoSize() {
    auto* w = new QWidget();
    auto* layout = new QVBoxLayout(w);
    layout->setSpacing(12);

    {
        auto* input = new ZInput();
        input->setPlaceholderText("Large");
        input->setInputSize(ZInput::kLarge);
        layout->addWidget(input);
    }
    {
        auto* input = new ZInput();
        input->setPlaceholderText("Default");
        input->setInputSize(ZInput::kDefault);
        layout->addWidget(input);
    }
    {
        auto* input = new ZInput();
        input->setPlaceholderText("Small");
        input->setInputSize(ZInput::kSmall);
        layout->addWidget(input);
    }

    layout->addStretch();
    return w;
}
