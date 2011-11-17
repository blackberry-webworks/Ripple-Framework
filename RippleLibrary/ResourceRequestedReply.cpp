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
#include "ResourceRequestedReply.h"

ResourceRequestedReply::ResourceRequestedReply(const QString id, const QUrl &url)
    : QNetworkReply(), m_substitute(false), m_id(id)
{
    offset = 0;
    setUrl(url);
    m_substitute = false;
}

qint64 ResourceRequestedReply::readData(char *data, qint64 maxSize)
{
    if (offset < content.size()) {
        qint64 number = qMin(maxSize, content.size() - offset);
        memcpy(data, content.constData() + offset, number);
        offset += number;
        return number;
    } else {
        return -1;
    }
}

bool ResourceRequestedReply::isSequential() const
{
    return true;
}

qint64 ResourceRequestedReply::bytesAvailable() const
{
    //Calling QNetworkReply::bytesAvailable() is required by all QNetworkReply
    //sub classes that return isSequential = true.
    //See QIODevice.cpp - bytesAvailable for documentation
    return content.size() + QNetworkReply::bytesAvailable() - offset;
}

void ResourceRequestedReply::respond(QVariantMap response)
{
    QString responseText = response["responseText"].toString();
    QString code = response["code"].toString();

    if (!m_substitute)
    {
        if (responseText == "deny")
        {
            open(ReadOnly | Unbuffered);
            setAttribute(QNetworkRequest::HttpStatusCodeAttribute, QVariant(403));
            setHeader(QNetworkRequest::ContentLengthHeader, QVariant(0));

            QTimer::singleShot(0, this, SIGNAL(readyRead()));
            QTimer::singleShot(0, this, SIGNAL(finished()));
        }
        else if (responseText == "substitute")
        {
            m_substitute =  true;
        }
    }
    else
    {
        open(ReadOnly | Unbuffered);
        this->content = responseText.toUtf8();
        setAttribute(QNetworkRequest::HttpStatusCodeAttribute, response["code"]);
        setHeader(QNetworkRequest::ContentLengthHeader, QVariant(this->content.size()));
        emit readyRead();
        emit finished();
    }
}
