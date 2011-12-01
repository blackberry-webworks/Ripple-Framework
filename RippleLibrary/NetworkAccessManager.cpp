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

#include "Global.h"
#include "NetworkAccessManager.h"
#include <QNetworkProxy>
#include <QNetworkRequest>
#include <QUuid>
#include "ResourceRequestedReply.h"
#include "LocalRequestReply.h"
#include "QtStageWebView.h"

NetworkAccessManager::NetworkAccessManager(QNetworkAccessManager *manager, QObject *parent)
    : QNetworkAccessManager(parent)
{
    setCache(manager->cache());
    setCookieJar(manager->cookieJar());
    setProxy(manager->proxy());
    setProxyFactory(manager->proxyFactory());
}

QNetworkReply *NetworkAccessManager::createRequest(
    QNetworkAccessManager::Operation operation, const QNetworkRequest &request,
    QIODevice *outgoingData)
{
    QNetworkRequest cRequest(request);

    if (headers.size() > 0) {
        QMapIterator<QString, QString> i(headers);
        while (i.hasNext())
        {
            i.next();
            cRequest.setRawHeader(i.key().toUtf8(), i.value().toUtf8());
        }
    }

    if (cRequest.url().scheme() == "local")
    {
        return new LocalRequestReply(cRequest.url());
    }
    else
    {
        QUuid id = QUuid::createUuid();

        //This is a sync call to TCPMessageHandler::onResourceRequested
        emit onResourceRequest(id, cRequest, outgoingData);

        ResourceRequestedReply *reply = pendingRequests.value(id);
        if (reply)
        {
            return reply;
        }
        else
        {
            return QNetworkAccessManager::createRequest(operation, cRequest, outgoingData);
        }
    }
}

void NetworkAccessManager::response(QVariantMap payload)
{
    QString id = payload["id"].toString();
    QString url = payload["url"].toString();
    QVariantMap response = payload["response"].toMap();
    QString responseText = response["responseText"].toString();

    if (responseText == "allow")
    {
        return;
    }
    else if (responseText == "deny" || responseText == "substitute")
    {
        ResourceRequestedReply *reply = new ResourceRequestedReply(id, url);
        connect(reply, SIGNAL(destroyed(QObject*)), this, SLOT(removeFromPending(QObject*)));
        pendingRequests.insert(id, reply);
        reply->respond(response);
    }
    else
    {
        ResourceRequestedReply *reply = pendingRequests.value(id);
        if (reply && reply->isSubstitute())
            reply->respond(response);
    }
}

void NetworkAccessManager::removeFromPending(QObject* destroyed)
{
    ResourceRequestedReply *reply = static_cast<ResourceRequestedReply*>(destroyed);
    if (reply)
        pendingRequests.remove(reply->getID());
}

void NetworkAccessManager::clearCustomHeaders()
{
    headers.clear();
}

void NetworkAccessManager::addCustomHeader(QString key, QString value)
{
    headers.insert(key, value);
}

const QMap<QString, QString> NetworkAccessManager::getCustomHeaders()
{
    return headers;
}
