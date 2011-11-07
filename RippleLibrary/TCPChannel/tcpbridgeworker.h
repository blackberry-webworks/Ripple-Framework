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

#ifndef TCPBRIDGEWORKER_H
#define TCPBRIDGEWORKER_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

#include "messagehandler.h"

namespace BlackBerry { 
namespace Ripple {
namespace TCPChannel {

class TCPBridgeworker : public QThread
{
  Q_OBJECT
  public:
      TCPBridgeworker(MessageHandler* pHandler, QHostAddress* host, int pn = 53533 ,QObject* parent = 0);
      virtual ~TCPBridgeworker();

protected:
     void run();

private slots:
     void newConnection();
     void readData();
private:
    MessageHandler* m_pMsgHandler;
    QTcpServer* m_pTcpServer;
    QTcpSocket *m_pClientConnection;
    QHostAddress*  m_pHostAddress;
    int port;
};
}}}
#endif // TCPBRIDGEWORKER_H
