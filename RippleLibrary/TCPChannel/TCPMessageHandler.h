﻿/*
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

#ifndef TCPMESSAGEHANDLER_H
#define TCPMESSAGEHANDLER_H

#include <QNetworkRequest>
#include <QGraphicsWebView>

#include "messagehandler.h"
#include "qtstagewebview.h"

namespace BlackBerry { 
namespace Ripple {
namespace TCPChannel {

static const int TCPChannel_MESSAGE_SETURL                = 0x0100;
static const int TCPChannel_MESSAGE_TEST2                 = 0x0101;

class TcpMessagehandler : public MessageHandler
{
    Q_OBJECT

private:
    QTcpSocket* m_pTcpConnection;

public:
    TcpMessagehandler(QObject *parent = 0);
    ~TcpMessagehandler();
    
    void setTcpConnection(QTcpSocket* conn)
    {
        m_pTcpConnection = conn;
    }

    void processMessage(Message* pMsg);

protected:
    void registerEvents();

private slots:
    void urlChanged(QString url);
    void onResourcerequested(QNetworkRequest* request);

private:
    virtual IRippleWebView* stageWebview()
    {
        return dynamic_cast<IRippleWebView*>(m_pWebView);
    }

  	virtual QtStageWebView* rimStageWebview()
	{
		return dynamic_cast<QtStageWebView*>(m_pWebView);
	}

    virtual QGraphicsWebView* graphicsWebview()
    {
        return dynamic_cast<QGraphicsWebView*>(m_pWebView);
    }
};
}}}
#endif // TCPMESSAGEHANDLER_H

