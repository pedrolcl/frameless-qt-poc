#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QMainWindow>

class FramelessWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit FramelessWindow(QWidget *parent = nullptr);
    QWidget *pseudoCaption() const;
    void setPseudoCaption(QWidget *widget);

protected:
    void updateCursor(Qt::Edges edges);
    bool event(QEvent* ev) override;

private:
    QWidget *m_pseudoCaption;
};

#endif
