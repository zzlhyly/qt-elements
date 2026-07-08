#include <QVBoxLayout>
#include <QWidget>
#include "widgets/input/zinput.h"

QWidget* ZInputDemoBasic() {
    auto* w = new QWidget();
    auto* layout = new QVBoxLayout(w);
    layout->setSpacing(12);

    auto* input = new ZInput();
    input->setPlaceholderText("Please input");
    layout->addWidget(input);

    layout->addStretch();
    return w;
}
