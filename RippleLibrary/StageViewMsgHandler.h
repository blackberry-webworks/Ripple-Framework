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

#ifndef RIPPLELIBRARY_STAGEVIEWMSGHANDLER_H_
#define RIPPLELIBRARY_STAGEVIEWMSGHANDLER_H_

#include "QtStageWebView.h"
#include "TCPChannel/MessageHandler.h"

using BlackBerry::Ripple::TCPChannel::MessageHandler;
using BlackBerry::Ripple::TCPChannel::Message;

namespace BlackBerry {
namespace Ripple {

class StageViewMsgHandler : public MessageHandler
{
  Q_OBJECT
  Q_PROPERTY(int serverPort READ getServerPort)

public:
    explicit StageViewMsgHandler(QObject *parent = 0);
    ~StageViewMsgHandler();
   

//stagewebview APIs
public slots:
    void loadUrl(const QString& url);
    void executeJavaScript(const QString& script);
    void crossOrigin(const bool allow);
    void customHTTPHeader(const QString& key, const QString& value);
    void setVisable(const bool isVisible);
    void setWindowGeometry(int x, int y, int w, int h);
    QString location();
    void historyBack();
    void historyForward();
    bool isHistoryBackEnabled();
    bool isHistoryForwardEnabled();
    int historyLength();
    int historyPosition();
    void historyPosition(int position);
    void setServerPort(int port);
    void setZoomFactor(float zoom);
    float zoomFactor();
  
   void processMessage(Message* pMsg);
   void processMessage(QVariantMap msg){}

 
    //following slots are used internal for emit signals which will be connected from js side
    void urlChanged(const QString& url);
    void javaScriptWindowObjectCleared();
    void reload();
 
//stagewebview events
signals:
    void locationChanged(const QString& url);
    void javaScriptWindowCleared();
    void javaScriptInjected();
    void onRequest(QObject* request);
    void onResponse(QObject* response);

protected:
    void registerEvents();

private:
    virtual IRippleWebView* stageWebview()
    {
        return dynamic_cast<IRippleWebView*>(m_pWebView);
    }

    virtual QtStageWebView* rimStageWebview()
    {
        return dynamic_cast<QtStageWebView*>(m_pWebView);
    }

    int getServerPort()
    {
        return _buildServerPort;
    }

private:
    int _buildServerPort;
};
}}
#endif  // RIPPLELIBRARY_STAGEVIEWMSGHANDLER_H_
