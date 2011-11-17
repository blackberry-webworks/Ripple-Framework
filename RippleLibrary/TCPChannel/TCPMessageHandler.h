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

#ifndef RIPPLELIBRARY_TCPCHANNEL_TCPMESSAGEHANDLER_H_
#define RIPPLELIBRARY_TCPCHANNEL_TCPMESSAGEHANDLER_H_

#include <QNetworkRequest>
#include <QGraphicsWebView>

#include "messagehandler.h"
#include "qtstagewebview.h"
#include <qjson/Parser.h>
#include <qjson/Serializer.h>
#include "ResourceRequestedReply.h"

namespace BlackBerry { 
namespace Ripple {
namespace TCPChannel {

static const QString EVENT = "event";
static const QString PAYLOAD = "payload";
static const QString RESOURCEREQUESTEDRESPONSE = "ResourceRequestedResponse";
static const QString WEBVIEWURLCHANGEREQUEST = "WebviewUrlChangeRequest";


class TcpMessagehandler : public MessageHandler
{
    Q_OBJECT

private:
    QTcpSocket* m_pTcpConnection;

public:
    TcpMessagehandler(QTcpSocket* conn = 0, QObject *parent = 0);
    ~TcpMessagehandler();
    void processMessage(Message* pMsg) {}
    void processMessage(QVariantMap msg);

protected:
    void registerEvents();

private slots:
    void urlChanged(QString url);
    void onResourceRequested(QUuid id, const QNetworkRequest &request);

    void tcpReadyRead(); 
    void tcpConnectionDisconnected();

private:

    QJson::Parser parser;

    virtual IRippleWebView* stageWebview()
    {
        return static_cast<IRippleWebView*>(m_pWebView);
    }

    virtual QtStageWebView* rimStageWebview()
    {
        return static_cast<QtStageWebView*>(m_pWebView);
    }

    virtual QGraphicsWebView* graphicsWebview()
    {
        return dynamic_cast<QGraphicsWebView*>(m_pWebView);
    }
};
}}}
#endif  // RIPPLELIBRARY_TCPCHANNEL_TCPMESSAGEHANDLER_H_

