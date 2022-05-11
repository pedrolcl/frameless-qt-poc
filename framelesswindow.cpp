#include <QDebug>
#include <QFlags>
#include <QWindow>
#include <QEvent>
#include <QHoverEvent>
#include <QStyle>
#include "framelesswindow.h"

FramelessWindow::FramelessWindow(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint),
      m_pseudoCaption(nullptr)
{ }

void FramelessWindow::updateCursor(Qt::Edges edges)
{
    if ( edges == 0 )
    {
        setCursor(Qt::ArrowCursor);
    }
    else if ( (edges == Qt::LeftEdge) ||
              (edges == Qt::RightEdge) )
    {
        setCursor(Qt::SizeHorCursor);
    }
    else if ( (edges == Qt::TopEdge) ||
              (edges == Qt::BottomEdge))
    {
        setCursor(Qt::SizeVerCursor);
    }
    else if ( (edges == (Qt::LeftEdge | Qt::TopEdge)) ||
              (edges == (Qt::RightEdge | Qt::BottomEdge)) )
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if ( (edges == (Qt::RightEdge | Qt::TopEdge)) ||
              (edges == (Qt::LeftEdge | Qt::BottomEdge)) )
    {
        setCursor(Qt::SizeBDiagCursor);
    }
}

bool FramelessWindow::event(QEvent* ev)
{
    static Qt::Edges edges = Qt::Edges();
    const int margin = style()->pixelMetric(QStyle::PM_LayoutTopMargin);

    switch (ev->type()) {
    case QEvent::MouseButtonPress:
        updateCursor(edges);
        if ((m_pseudoCaption != nullptr) && m_pseudoCaption->underMouse()) {
            windowHandle()->startSystemMove();
        } else if (edges != 0) {
            windowHandle()->startSystemResize(edges);
            show();
        }
        break;
    case QEvent::MouseButtonRelease:
        qDebug() << Q_FUNC_INFO << ev;
        edges = Qt::Edges();
        updateCursor(edges);
        setFocus();
        break;
    case QEvent::HoverEnter:
        edges = Qt::Edges();
        break;
    case QEvent::HoverLeave:
        edges = Qt::Edges();
        break;
    case QEvent::HoverMove: {
        edges = Qt::Edges();
        QHoverEvent *event = static_cast<QHoverEvent*>(ev);
        QPoint p =
    #if QT_VERSION < QT_VERSION_CHECK(6,0,0)
                    event->pos();
    #else
                    event->position().toPoint();
    #endif
        if ( p.x() < margin ) {
            edges |= Qt::LeftEdge;
        }
        if ( p.x() > (width() - margin) ) {
            edges |= Qt::RightEdge;
        }
        if ( p.y() < margin ) {
            edges |= Qt::TopEdge;
        }
        if ( p.y() > (height() - margin) ) {
            edges |= Qt::BottomEdge;
        }
        updateCursor(edges);
        break;
    }
    default:
        break;
    }
    return QMainWindow::event(ev);
}

QWidget *FramelessWindow::pseudoCaption() const
{
    return m_pseudoCaption;
}

void FramelessWindow::setPseudoCaption(QWidget *widget)
{
    m_pseudoCaption = widget;
}
