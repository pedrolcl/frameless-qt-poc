/*
    FramelessWindow Demo for Qt Applications
    Copyright (c) 2022, Pedro López-Cabanillas <plcl@users.sf.net>. All rights reserved.
    Copyright (c) 2023 CM0use

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
       contributors may be used to endorse or promote products derived from
       this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
    switch (edges) {
    case 0:
        setCursor(Qt::ArrowCursor);
        break;
    case Qt::LeftEdge:
    case Qt::RightEdge:
        setCursor(Qt::SizeHorCursor);
        break;
    case Qt::TopEdge:
    case Qt::BottomEdge:
        setCursor(Qt::SizeVerCursor);
        break;
    case Qt::LeftEdge | Qt::TopEdge:
    case Qt::RightEdge | Qt::BottomEdge:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case Qt::RightEdge | Qt::TopEdge:
    case Qt::LeftEdge | Qt::BottomEdge:
        setCursor(Qt::SizeBDiagCursor);
        break;
    }
}

bool FramelessWindow::event(QEvent* ev)
{
    if (windowFlags() & Qt::FramelessWindowHint) {
        static Qt::Edges edges = Qt::Edges();
        const int margin = style()->pixelMetric(QStyle::PM_LayoutTopMargin);
        switch (ev->type()) {
        case QEvent::MouseButtonPress:
            updateCursor(edges);
            if ((m_pseudoCaption != nullptr) && m_pseudoCaption->underMouse()) {
                auto ok = windowHandle()->startSystemMove();
                qDebug() << "startSystemMove()" << (ok ? "succeeded" : "failed");
            } else if (edges != 0) {
                auto ok = windowHandle()->startSystemResize(edges);
                qDebug() << "startSystemResize()" << (ok ? "succeeded" : "failed");
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
