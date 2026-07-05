#include <QApplication>

#include "testwidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    
    TestWidget tw;
    tw.setMinimumSize(1280, 720);
    tw.show();
    return app.exec();
}