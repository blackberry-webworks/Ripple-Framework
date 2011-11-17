/*
* Copyright 2010-2011 Research In Motion Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <QtCore/QCoreApplication>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTcpSocket* tcpSocket = new QTcpSocket(0);
    tcpSocket->connectToHost("127.0.0.1", 53533);
    if (tcpSocket->waitForConnected ())
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out << "http://www.google.ca";
        tcpSocket->write(block);
    }
    return a.exec();
}
