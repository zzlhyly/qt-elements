#include "mywidget.h"
#include <QApplication>

int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);
    MyWidget widget;
    widget.initialize();
    widget.resize(400, 300);
    widget.show();
    return app.exec();
}