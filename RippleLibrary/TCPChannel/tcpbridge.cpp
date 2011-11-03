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

#include "stdafx.h"
#include "tcpbridge.h"
#include "messagehandler.h"
#include "tcpbridgeworker.h"

using namespace BlackBerry::Ripple::TCPChannel;

TCPBridge::TCPBridge(QObject* parent) 
    : QObject(parent), m_pWorker(0) 
{
}

TCPBridge::~TCPBridge()
{
  Stop();
}

void TCPBridge::Start()
{ 
  QHostAddress* ha = new QHostAddress(QHostAddress::LocalHost);
  m_pWorker = new TCPBridgeworker(m_pMsgHandler, ha);    
  m_pWorker->start();
}

void TCPBridge::Stop()
{
  if ( m_pWorker->isRunning())
  {
    qDebug() << "Stop monitoring thread";
    m_pWorker->exit();
  }
}

void TCPBridge::RegisterMessageHandler(MessageHandler* pHandler)
{
    m_pMsgHandler = pHandler;
}
