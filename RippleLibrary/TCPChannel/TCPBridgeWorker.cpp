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

using namespace BlackBerry::Ripple::TCPChannel;

TCPBridgeworker* TCPBridgeworker::server()
{
    if (!s_tcpServer)
        s_tcpServer = new TCPBridgeworker();
    return s_tcpServer;
}

TCPBridgeworker::TCPBridgeworker(QObject* parent) 
    : QObject(parent), m_pTcpServer(0), m_pWebView(0)
{
}

TCPBridgeworker::~TCPBridgeworker()
{
    close();
}

void TCPBridgeworker::listen(int port)
{
    if (m_pTcpServer)
        return;
    m_pTcpServer = new QTcpServer();
    if ( !m_pTcpServer->listen(QHostAddress::LocalHost, port) )
    {
        QMessageBox::critical(0, tr("WebView TCP Server"), tr("Unable to start the server: %1.").arg(m_pTcpServer->errorString()));
        close();
        return;
    }
    connect(m_pTcpServer, SIGNAL( newConnection()), this, SLOT(newConnection()));
}

void TCPBridgeworker::newConnection()
{
    QTcpSocket* tcpConnection = m_pTcpServer->nextPendingConnection();
    TcpMessagehandler* handler = new TcpMessagehandler(tcpConnection, this);
    Q_ASSERT(m_pWebView);
    handler->Register(m_pWebView);
}

void TCPBridgeworker::close()
{
    if (m_pTcpServer) 
    {
        m_pTcpServer->close();
        delete m_pTcpServer;
    }
    m_pTcpServer = 0;
    s_tcpServer = 0;
    deleteLater();
}