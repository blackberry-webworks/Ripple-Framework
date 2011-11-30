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

#ifndef RIPPLELIBRARY_NETWORKACCESSMANAGER_H_
#define RIPPLELIBRARY_NETWORKACCESSMANAGER_H_

#include <QNetworkAccessManager>
#include "ResourceRequestedReply.h"
#include <QUuid>

class NetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    NetworkAccessManager(QNetworkAccessManager *manager, QObject *parent);
    void clearCustomHeaders();
    void addCustomHeader(QString key, QString value);
    const QMap<QString, QString> getCustomHeaders();
    void response(QVariantMap payload);

signals:
    void onResourceRequest(QUuid id, const QNetworkRequest &request, QIODevice *outgoingData);

protected:
    QNetworkReply* createRequest(QNetworkAccessManager::Operation operation,
    const QNetworkRequest &request, QIODevice *device);

private:
    ResourceRequestedReply *reply;
    QMap<QString, ResourceRequestedReply*> pendingRequests;
    QMap<QString, QString> headers;

private slots:
    void removeFromPending(QObject* reply);
};

#endif  // RIPPLELIBRARY_NETWORKACCESSMANAGER_H_
