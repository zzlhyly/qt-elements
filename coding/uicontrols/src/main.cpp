#include <QApplication>

#include "gallery.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Gallery gallery;
    gallery.setMinimumSize(1280, 720);
    gallery.show();
    return app.exec();
}
