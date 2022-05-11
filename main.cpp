#include <QApplication>
#include "demowindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DemoWindow w;
    w.show();
    return app.exec();
}
