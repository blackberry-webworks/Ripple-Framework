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

#ifndef RIPPLELIBRARY_LOCALREQUESTREPLY_H_
#define RIPPLELIBRARY_LOCALREQUESTREPLY_H_

#include <QNetworkReply>
#include <QUrlInfo>
#include <QFile>

static const QString LOCAL_BASE_PATH = "/bbxlocal/";
static const QString LOCAL_PROTOCOL = "local://";

class LocalRequestReply : public QNetworkReply
{
    Q_OBJECT

public:
    explicit LocalRequestReply(const QUrl &url);
    qint64 bytesAvailable() const;
    void abort(){}
    bool isSequential() const;

protected:
    qint64 readData(char *data, qint64 maxSize);

private:
    qint64 offset;
    QByteArray content;
    QMap<QString, QString> types;

private slots:
    void setContent();
};
#endif  // RIPPLELIBRARY_LOCALREQUESTREPLY_H_
