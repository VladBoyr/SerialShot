/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "include/serialshot.h"

SerialShot::SerialShot()
{
    shotCounter = 0;

    timer = new QTimer(this);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(shootScreen()));

    startSerialShotButton = createButton(tr("Start Serial Screenshot"), this, SLOT(startSerialShot()));
    stopSerialShotButton = createButton(tr("Stop Serial Screenshot"), this, SLOT(stopSerialShot()));
    stopSerialShotButton->setDisabled(true);
    quitSerialShotButton = createButton(tr("Quit"), this, SLOT(close()));

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(startSerialShotButton);
    mainLayout->addWidget(stopSerialShotButton);
    mainLayout->addWidget(quitSerialShotButton);
    setLayout(mainLayout);

    setWindowTitle(tr("Serial Screenshot"));
    resize(300, 50);
}

QPushButton *SerialShot::createButton(const QString &text, QWidget *receiver, const char *member)
{
    QPushButton *button = new QPushButton(text);
    button->connect(button, SIGNAL(clicked()), receiver, member);
    return button;
}

void SerialShot::startSerialShot()
{
    QThread::msleep(5000);
    startSerialShotButton->setDisabled(true);
    stopSerialShotButton->setDisabled(false);
    timer->start();
}

void SerialShot::stopSerialShot()
{
    startSerialShotButton->setDisabled(false);
    stopSerialShotButton->setDisabled(true);
    timer->stop();
}

void SerialShot::shootScreen()
{
    QPixmap originalPixmap = QPixmap();

    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen)
    {
        originalPixmap = screen->grabWindow(0);

        QString format = "bmp";
        QString fileName = QDir::currentPath() + tr("/untitled") +
                QString::number(shotCounter++) + tr(".") + format;

        if (!fileName.isEmpty())
        {
            originalPixmap.save(fileName, format.toLatin1().constData());
        }
    }
}
