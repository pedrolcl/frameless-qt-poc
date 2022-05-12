/*
    FramelessWindow Demo for Qt Applications
    Copyright (c) 2022, Pedro López-Cabanillas <plcl@users.sf.net>. All rights reserved.

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
#include <QApplication>
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
    qDebug() << Q_FUNC_INFO << "running on" << qApp->platformName();
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

    int margin = style()->pixelMetric(QStyle::PM_LayoutTopMargin);
    QVBoxLayout *vlayout = new QVBoxLayout(central);
    vlayout->setContentsMargins(margin, margin, margin, margin);
    vlayout->addWidget(toolbar);
    vlayout->addWidget(textEdit);

    setPseudoCaption(toolbar);
}
