#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "widgets/input/zinput.h"

QWidget* ZInputDemoPrependAppend() {
    auto* w = new QWidget();
    auto* layout = new QVBoxLayout(w);
    layout->setSpacing(12);

    auto* input = new ZInput();
    input->setPlaceholderText("Enter URL");
    input->setPrependWidget(new QLabel("http://"));
    input->setAppendWidget(new QPushButton(".com"));
    layout->addWidget(input);

    layout->addStretch();
    return w;
}
