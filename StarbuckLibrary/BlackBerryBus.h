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

#ifndef BLACKBERRYBUS_H
#define BLACKBERRYBUS_H

#include <QWebView>
#include <QObject>
#include "QtStageWebView.h"

namespace BlackBerry {
namespace Starbuck {

const QString eventbusSource("window.eventbus = (function() {\
        var _objMap = new Object();\
        var _eventbus = parent.eventbus2;\
        delete parent.eventbus2;\
            return {\
                on: function(event, what) {\
                    var fname = _eventbus.on(event, \"function\");\
                    _objMap[fname] = what;\
                },\
                trigger: function(event, data, blah) {\
                    var fnames = _eventbus.getFunctionName(event);\
                    fnames = fnames.split(\";\");\
                    for(var i = 0; i<fnames.length; i++) {\
                        var prop = fnames[i];\
                        if (_objMap[prop])\
                            eval(_objMap[prop](data));\
                        else\
                            _eventbus.trigger(event, data);\
                        }\
                },\
                internal: function(event, data) {\
                    var fnames = _eventbus.getFunctionName(event);\
                    fnames = fnames.split(\";\");\
                    for(var i = 0; i<fnames.length; i++) {\
                        var prop = fnames[i];\
                            eval(_objMap[prop](data));\
                        }\
                }\
            };\
        })();");

struct CallbackInfo
{
    QString function;
    QWebFrame *frame;
};

class BlackBerryBus : public QObject
{
  Q_OBJECT
public:
  BlackBerryBus(QObject *parent, QWebFrame *webFrame);
  ~BlackBerryBus();
private:
  static QMap<QString, QList<CallbackInfo>*> _listener;
  bool _async;
  QWebFrame *m_pWebFrame;
  QtStageWebView *m_pInternalWebView;
  QString generateRandomFunctionName();

public slots:
  void trigger(QString eventName, QString jsonData, bool async);
  void trigger(QString eventName, QString jsonData);
  QString on(QString eventName, QString jsonCallback);
  QString getFunctionName(QString input);
};

}
}

#endif
