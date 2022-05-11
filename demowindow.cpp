#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QStyle>
#include "demowindow.h"

DemoWindow::DemoWindow(QWidget *parent): FramelessWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    QToolButton *appMenu = new QToolButton(this);
    appMenu->setAutoRaise(true);
    appMenu->setIcon(QIcon::fromTheme("application-menu"));
    appMenu->setPopupMode(QToolButton::InstantPopup);
    QMenu *popup = new QMenu(this);
    QAction *minimize = new QAction("Minimize", this);
    connect(minimize, &QAction::triggered, this, [this]{
        this->setWindowState(Qt::WindowMinimized);
    });
    QAction *exit = new QAction("Quit", this);
    connect(exit, &QAction::triggered, this, &FramelessWindow::close);
    popup->addAction(minimize);
    popup->addSeparator();
    popup->addAction(exit);
    appMenu->setMenu(popup);

    QToolButton *closeButton = new QToolButton(this);
    closeButton->setAutoRaise(true);
    closeButton->setIcon(QIcon::fromTheme("window-close"));
    connect(closeButton, &QToolButton::clicked, this, &FramelessWindow::close);

    QFrame *toolbar = new QFrame;
    QHBoxLayout *hlayout = new QHBoxLayout(toolbar);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(new QLabel("FramelessWindow Demo"));
    hlayout->addStretch();
    hlayout->addWidget(appMenu);
    hlayout->addWidget(closeButton);

    QTextEdit *textEdit = new QTextEdit;
    textEdit->setReadOnly(true);
    textEdit->setText("This window has no frame, but can be moved and resized...");

    int margin = style()->pixelMetric(QStyle::PM_DefaultTopLevelMargin);
    QVBoxLayout *vlayout = new QVBoxLayout(central);
    vlayout->setContentsMargins(margin, margin, margin, margin);
    vlayout->addWidget(toolbar);
    vlayout->addWidget(textEdit);

    setPseudoCaption(toolbar);
}
