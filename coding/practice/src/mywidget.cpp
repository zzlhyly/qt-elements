#include "mywidget.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QTimer>


void MyWidget::initialize()
{
    // Set up the layout and other initialization code here
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
    // Additional cleanup or actions before closing can be added here
    QTimer::singleShot(10 * 1000, qApp, []() {
        qApp->quit(); // Ensure the application quits when the widget is closed
    });
}