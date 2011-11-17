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

#ifndef RIPPLELIBRARY_RESOURCEREQUESTEDREPLY_H_
#define RIPPLELIBRARY_RESOURCEREQUESTEDREPLY_H_

#include <QNetworkReply>
#include <QUrlInfo>

class ResourceRequestedReply : public QNetworkReply
{
    Q_OBJECT

public:
    ResourceRequestedReply(QString id, const QUrl &url);
    qint64 bytesAvailable() const;
    void abort(){}
    bool isSequential() const;
    void respond(QVariantMap response);
    bool isSubstitute() {return m_substitute;}
    QString getID() {return m_id;}

protected:
    qint64 readData(char *data, qint64 maxSize);

private:
    QString m_id;
    qint64 offset;
    QByteArray content;
    bool m_substitute;
};
#endif  // RIPPLELIBRARY_RESOURCEREQUESTEDREPLY_H_
