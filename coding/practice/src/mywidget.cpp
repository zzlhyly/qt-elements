#include "mywidget.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

void MyWidget::initialize()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

    QPushButton *button = new QPushButton("Click Me", this);
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, []() {
        qDebug("Button clicked!");
    });
}

void MyWidget::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    qDebug("MyWidget is closing.");
    qApp->quit();
}