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
#include "TCPBridgeWorker.h"
#include "TCPMessageHandler.h"
#include <qjson/Parser.h>

using namespace BlackBerry::Ripple::TCPChannel;

TCPBridgeworker::TCPBridgeworker(MessageHandler* pHandler, QHostAddress* host, int pn, QObject* parent) 
    : QThread(parent), m_pMsgHandler(pHandler), m_pTcpServer(0), m_pClientConnection(0), m_pHostAddress(host), port(pn)
{
}

TCPBridgeworker::~TCPBridgeworker()
{
    if ( m_pTcpServer )
    {
        m_pTcpServer->close();
        delete m_pTcpServer;
        m_pTcpServer = 0;
    }
    if ( m_pHostAddress )
        delete m_pHostAddress;
}

void TCPBridgeworker::run()
{
    m_pTcpServer = new QTcpServer(0);
    connect(m_pTcpServer, SIGNAL( newConnection()), this, SLOT(newConnection()));
    if ( !m_pTcpServer->listen( *m_pHostAddress, port) )
    {
        QMessageBox::critical(0, tr("WebView TCP Server"), tr("Unable to start the server: %1.").arg(m_pTcpServer->errorString()));
        m_pTcpServer->close();
        delete m_pTcpServer;
        m_pTcpServer = 0;
        return;
    }
    exec();
}

void TCPBridgeworker::newConnection()
{
    m_pClientConnection = m_pTcpServer->nextPendingConnection();
    TcpMessagehandler* tcpMsghandler = dynamic_cast<TcpMessagehandler*>(m_pMsgHandler);
    tcpMsghandler->setTcpConnection(m_pClientConnection);
    connect(m_pClientConnection, SIGNAL(disconnected()), m_pClientConnection, SLOT(deleteLater()));
    connect(m_pClientConnection, SIGNAL(readyRead()), this, SLOT(readData()));
    
    //We might have already misses the readyRead signal
    //call readData just to make sure
    readData();
}

void TCPBridgeworker::readData()
{
    if (m_pClientConnection && m_pClientConnection->bytesAvailable())
    {
        QJson::Parser parser;
        bool ok;

        QVariantMap result; // = parser.parse("[1,2,3]", &ok);


        QByteArray data = m_pClientConnection->read(m_pClientConnection->bytesAvailable());

        result = parser.parse(data, &ok).toMap();

        if (!ok)
            qDebug() << "something went wrong during the conversion";
        else
            qDebug() << "converted to" << result;

        m_pMsgHandler->processMessage(result);
    }
}
