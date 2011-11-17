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

#ifndef RIPPLELIBRARY_TCPCHANNEL_TCPBRIDGEWORKER_H_
#define RIPPLELIBRARY_TCPCHANNEL_TCPBRIDGEWORKER_H_

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

#include "MessageHandler.h"
#include "QtStageWebView.h"

namespace BlackBerry {
namespace Ripple {
namespace TCPChannel {

class TCPBridgeworker : public QObject
{
    Q_OBJECT
public:
    explicit TCPBridgeworker(QObject* parent = 0);
    virtual ~TCPBridgeworker();
    static TCPBridgeworker* server();
    void setWebView(QtStageWebView* pView) { m_pWebView = pView;}
    void listen(int port = 53533);
protected:
    void close();
private slots:
    void newConnection();
private:
    QTcpServer* m_pTcpServer;
    QtStageWebView* m_pWebView;
};
static TCPBridgeworker* s_tcpServer;
}}}
#endif  // RIPPLELIBRARY_TCPCHANNEL_TCPBRIDGEWORKER_H_
