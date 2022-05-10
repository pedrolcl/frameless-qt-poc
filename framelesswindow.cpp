#include <QDebug>
#include <QFrame>
#include <QFlags>
#include <QWindow>
#include <QToolButton>
#include <QTextEdit>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QEvent>
#include <QHoverEvent>
#include "framelesswindow.h"

const int margin = 11;

FramelessWindow::FramelessWindow(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint)
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

    m_toolbar = new QFrame;
    QHBoxLayout *hlayout = new QHBoxLayout(m_toolbar);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(new QLabel("FramelessWindow Demo"));
    hlayout->addStretch();
    hlayout->addWidget(appMenu);
    hlayout->addWidget(closeButton);

    QTextEdit *textEdit = new QTextEdit;
    textEdit->setReadOnly(true);
    textEdit->setText("This window has no frame, but can be moved and resized...");

    QVBoxLayout *vlayout = new QVBoxLayout(central);
    vlayout->setContentsMargins(margin, margin, margin, margin);
    vlayout->addWidget(m_toolbar);
    vlayout->addWidget(textEdit);
}

void FramelessWindow::updateCursor()
{
    if ( m_edges == 0 )
    {
        setCursor(Qt::ArrowCursor);
    }
    else if ( (m_edges == Qt::LeftEdge) ||
              (m_edges == Qt::RightEdge) )
    {
        setCursor(Qt::SizeHorCursor);
    }
    else if ( (m_edges == Qt::TopEdge) ||
              (m_edges == Qt::BottomEdge))
    {
        setCursor(Qt::SizeVerCursor);
    }
    else if ( (m_edges == (Qt::LeftEdge | Qt::TopEdge)) ||
              (m_edges == (Qt::RightEdge | Qt::BottomEdge)) )
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if ( (m_edges == (Qt::RightEdge | Qt::TopEdge)) ||
              (m_edges == (Qt::LeftEdge | Qt::BottomEdge)) )
    {
        setCursor(Qt::SizeBDiagCursor);
    }
}

bool FramelessWindow::event(QEvent* ev)
{
    switch (ev->type()) {
    case QEvent::MouseButtonPress:
        updateCursor();
        if (m_toolbar->underMouse()) {
            windowHandle()->startSystemMove();
        } else if (m_edges != 0) {
            windowHandle()->startSystemResize(m_edges);
        }
        break;
    case QEvent::MouseButtonRelease:
        qDebug() << Q_FUNC_INFO << ev;
        m_edges = Qt::Edges();
        updateCursor();
        setFocus();
        break;
    case QEvent::HoverEnter:
        m_edges = Qt::Edges();
        break;
    case QEvent::HoverLeave:
        m_edges = Qt::Edges();
        break;
    case QEvent::HoverMove: {
        m_edges = Qt::Edges();
        QHoverEvent *event = static_cast<QHoverEvent*>(ev);
        QPoint p =
    #if QT_VERSION < QT_VERSION_CHECK(6,0,0)
                    event->pos();
    #else
                    event->position().toPoint();
    #endif
        if ( p.x() < margin ) {
            m_edges |= Qt::LeftEdge;
        }
        if ( p.x() > (width() - margin) ) {
            m_edges |= Qt::RightEdge;
        }
        if ( p.y() < margin ) {
            m_edges |= Qt::TopEdge;
        }
        if ( p.y() > (height() - margin) ) {
            m_edges |= Qt::BottomEdge;
        }
        updateCursor();
        break;
    }
    default:
        break;
    }
    return QMainWindow::event(ev);
}

