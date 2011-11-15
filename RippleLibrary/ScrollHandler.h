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

#ifndef RIPPLELIBRARY_SCROLLHANDLER_H_
#define RIPPLELIBRARY_SCROLLHANDLER_H_

#include "Global.h"
#include <QMutex>
#include <QEvent>
#include "QtStageWebView.h"

class ScrollHandler : public QObject {
    Q_OBJECT
    QtStageWebView *m_pWebView;
    QTimer *m_pTimer;
    QMutex *m_pMutex;
    bool m_flag;
public:
    explicit ScrollHandler(QtStageWebView *parent);
    ~ScrollHandler();
public slots:
    void unlock();
    
protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif  // RIPPLELIBRARY_SCROLLHANDLER_H_
