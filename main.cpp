#include <QApplication>
#include "framelesswindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FramelessWindow w;
    w.show();
    return app.exec();
}
