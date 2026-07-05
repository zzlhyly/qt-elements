#include "mywidget.h"
#include <QApplication>

int main(int argc, char *argv[]) 
{
    QApplication::setQuitOnLastWindowClosed(false);
    QApplication::setApplicationName("Practice Application");
    QApplication::setOrganizationName("My Organization");
    QApplication::setApplicationVersion("1.0.0");
    QApplication app(argc, argv);
    MyWidget widget;
    widget.setObjectName("MyWidget");
    widget.initialize();
    widget.resize(400, 300);
    widget.show();
    return app.exec();
}