#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QMainWindow>

class QFrame;

class FramelessWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FramelessWindow(QWidget *parent = nullptr);

protected:
    void updateCursor();
    bool event(QEvent* ev) override;

private:
    Qt::Edges m_edges;
    QFrame *m_toolbar;
};

#endif
