#ifndef DEMOWINDOW_H
#define DEMOWINDOW_H

#include <QObject>
#include <QWidget>
#include "framelesswindow.h"

class DemoWindow : public FramelessWindow
{
    Q_OBJECT
public:
    explicit DemoWindow(QWidget *parent = nullptr);
};

#endif // DEMOWINDOW_H
