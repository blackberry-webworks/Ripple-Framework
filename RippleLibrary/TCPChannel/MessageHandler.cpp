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

#include "Global.h"
#include "MessageHandler.h"

//static const int IPCChannel_MESSAGE_TEST1                 = 0x0100;
//static const int IPCChannel_MESSAGE_TEST2                 = 0x0101;

using namespace BlackBerry::Ripple::TCPChannel;

MessageHandler::MessageHandler(QObject *parent)
  : QObject(parent), m_pWebView(0)
{
}

MessageHandler::~MessageHandler()
{
}

void MessageHandler::sendMessage(int id, const QString& msg)
{
  QByteArray a;
  QBuffer b(&a);
  b.open(QIODevice::WriteOnly);
  QDataStream out(&b);
  out << msg;
  int size = a.size();
  Message* pMsg = new Message(id, size, &a);
  EmitMessage(pMsg);
  qDebug() << "Message:" << msg << " sent!";
  delete pMsg;
}    
