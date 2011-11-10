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
#include <qjson/Serializer.h>

using namespace BlackBerry::Ripple::TCPChannel;

TcpMessagehandler::TcpMessagehandler(QObject *parent)
  : MessageHandler(parent),m_pTcpConnection(0),bWaitForRequestresponse(false)
{

}

TcpMessagehandler::~TcpMessagehandler()
{

}

void TcpMessagehandler::processMessage(Message* pMsg)
{
    int msgID = pMsg->ID();
    QString url( *pMsg->Data());
    qDebug() << "Message TEST1 received, ID:" << msgID << "Data:" << url << " received!";
    m_pWebView->loadURL(url);
    delete pMsg;
}

void TcpMessagehandler::processMessage(QVariantMap msg)
{
    QString event = msg["event"].toString();
    if ( bWaitForRequestresponse && event != "ResourceRequestedResponse" )
    {
        qDebug() << "event:" << event << "not what we expected, keep waiting";
        m_pTcpConnection->waitForReadyRead();
        return;
    }
    if ( event == "ResourceRequestedResponse" )
    {
        QVariantMap payload = msg["payload"].toMap();
        QString url = payload["url"].toString();
        QString response = payload["response"].toString();        
        graphicsWebview()->page()->mainFrame()->setAllowAccess(response != "deny");
    }
    else if ( event == "WebviewUrlChangeRequest" )
    {
        QString payload = msg["payload"].toString();
        m_pWebView->loadURL(payload);
    }
}

void TcpMessagehandler::registerEvents()
{
    connect(rimStageWebview(), SIGNAL(urlChanged(QString)), this, SLOT(urlChanged(QString)));
    connect(graphicsWebview()->page()->mainFrame(), SIGNAL(onResourceRequest(QNetworkRequest*)), this, SLOT(onResourcerequested(QNetworkRequest*)));
}

void TcpMessagehandler::urlChanged(QString url) 
{
}

void TcpMessagehandler::onResourcerequested(QNetworkRequest* req)
{
    if ( m_pTcpConnection )
    {
        QString url = req->url().toString();
        QVariantMap msgToSend;
        msgToSend.insert("event", "ResourceRequested");
        msgToSend.insert("payload", url);
        QJson::Serializer serializer;
        QByteArray json = serializer.serialize(msgToSend); 
        qDebug() << json;
        sendMessage(json, m_pTcpConnection);
        bWaitForRequestresponse = true;
        m_pTcpConnection->waitForReadyRead();
    }
}
