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

#ifndef TCPBRIDGE_H
#define TCPBRIDGE_H

#include <QObject>
#include <QString>
#include "tcpbridgeworker.h"
#include "messagehandler.h"

namespace BlackBerry {
namespace Ripple {
namespace TCPChannel {

class TCPBridge : public QObject
{
    Q_OBJECT
public:
    TCPBridge(QObject* parent = 0);
    virtual ~TCPBridge();
public:
    void Start();
    void Stop();    
    void RegisterMessageHandler(MessageHandler* pHandler);

signals:

private:
    TCPBridgeworker* m_pWorker;
    MessageHandler* m_pMsgHandler;
};
}}}
#endif // TCPBRIDGE_H
