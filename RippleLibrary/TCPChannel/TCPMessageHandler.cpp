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

#include "Global.h"
#include "TCPMessageHandler.h"
#include "NetworkAccessManager.h"

using BlackBerry::Ripple::TCPChannel::TcpMessagehandler;

TcpMessagehandler::TcpMessagehandler(QTcpSocket* conn, QObject *parent)
  : MessageHandler(parent), m_pTcpConnection(conn)
{
    connect(m_pTcpConnection, SIGNAL(readyRead()), SLOT(tcpReadyRead()));
    connect(m_pTcpConnection, SIGNAL(disconnected()), SLOT(tcpConnectionDisconnected()));
    tcpReadyRead();
}

TcpMessagehandler::~TcpMessagehandler()
{
}

void TcpMessagehandler::tcpReadyRead()
{
    if (m_pTcpConnection && m_pTcpConnection->bytesAvailable())
    {
        bool ok;
        QVariantMap result;
        QByteArray data = m_pTcpConnection->read(m_pTcpConnection->bytesAvailable());
        result = parser.parse(data, &ok).toMap();

        if (!ok)
            qDebug() << "something went wrong during the conversion";
        else
            processMessage(result);
    }
}

void TcpMessagehandler::tcpConnectionDisconnected()
{
    if ( m_pTcpConnection )
    {
        m_pTcpConnection->deleteLater();
        m_pTcpConnection = 0;
    }
}

void TcpMessagehandler::processMessage(QVariantMap msg)
{
    QString event = msg[EVENT].toString();
    if ( event == RESOURCEREQUESTEDRESPONSE )
    {
        QVariantMap payload = msg[PAYLOAD].toMap();
        NetworkAccessManager *networkAccessManager = reinterpret_cast<NetworkAccessManager*>(graphicsWebview()->page()->networkAccessManager());
        networkAccessManager->response(payload);
    }
    else if ( event == WEBVIEWURLCHANGEREQUEST )
    {
        QString payload = msg[PAYLOAD].toString();
        m_pWebView->loadURL(payload);
    }
}

void TcpMessagehandler::registerEvents()
{
    connect(rimStageWebview(), SIGNAL(urlChanged(QString)), this, SLOT(urlChanged(QString)));
    connect(graphicsWebview()->page()->networkAccessManager(), SIGNAL(onResourceRequest(QUuid, QNetworkRequest)), this, SLOT(onResourceRequested(QUuid, QNetworkRequest)));
}

void TcpMessagehandler::urlChanged(QString url)
{
}

void TcpMessagehandler::onResourceRequested(QUuid id, const QNetworkRequest &req)
{
    if ( m_pTcpConnection )
    {
        m_pTcpConnection->disconnect(SIGNAL(readyRead()));
        QVariantMap msgToSend;
        QVariantMap payload;
        payload.insert("id", id.toString());
        payload.insert("url", req.url().toString());
        msgToSend.insert("event", "ResourceRequested");
        msgToSend.insert("payload", payload);
        QJson::Serializer serializer;
        QByteArray json = serializer.serialize(msgToSend);
        sendMessage(json, m_pTcpConnection);
        m_pTcpConnection->waitForBytesWritten();
        if ( m_pTcpConnection->waitForReadyRead())
        {
            tcpReadyRead();
        }
        connect(m_pTcpConnection, SIGNAL(readyRead()), SLOT(tcpReadyRead()));
    }
}
