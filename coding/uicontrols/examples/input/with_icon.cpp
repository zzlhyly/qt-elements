#include <QHBoxLayout>
#include <QWidget>
#include "widgets/input/zinput.h"
#include "input/input_demos.h"

QWidget* ZInputDemoWithIcon() {
    auto* w = new QWidget();
    auto* row = new QHBoxLayout(w);
    row->setSpacing(12);

    {
        auto* input = new ZInput();
        input->setPlaceholderText("Search");
        input->setPrefixIcon(QChar(0x1F50D));
        row->addWidget(input);
    }
    {
        auto* input = new ZInput();
        input->setPlaceholderText("Email");
        input->setSuffixIcon(QChar(0x2709));
        row->addWidget(input);
    }

    row->addStretch();
    return w;
}
