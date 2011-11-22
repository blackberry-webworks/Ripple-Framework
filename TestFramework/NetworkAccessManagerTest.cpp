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

#include "NetworkAccessManagerTest.h"
#include "QtStageWebView.h"

Q_DECLARE_METATYPE(QUuid);

TEST(NetworkAccessManager, CanSignalOnResourceRequest)
{
    QtStageWebView webview;
    webview.continueLoad();
    NetworkAccessManager* manager = dynamic_cast<NetworkAccessManager*>(webview.page()->networkAccessManager());
    Q_ASSERT(manager != 0);

    QString location = "http://www.targetresource.ca/";

    int idQUuid = qRegisterMetaType<QUuid>();
    int idNetworkRequest = qRegisterMetaType<QNetworkRequest>();

    QSignalSpy spy(manager, SIGNAL(onResourceRequest(QUuid, QNetworkRequest)));

    // Create an event loop to wait for the loadFinished when loading webpages
    QEventLoop loop;
    QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));
    webview.loadURL(location);
    loop.exec();

    ASSERT_EQ(1, spy.count());
    //Verify arguments
    QList<QVariant> arguments = spy.takeFirst();
    EXPECT_EQ(2, arguments.length());
    QVariant first = arguments.at(0);
    QVariant second = arguments.at(1);
    std::string firsttype(first.typeName());
    EXPECT_EQ("QUuid", firsttype);
    std::string sectype(second.typeName());
    EXPECT_EQ("QNetworkRequest", sectype);
    QNetworkRequest request = qvariant_cast<QNetworkRequest>(second);
    QUrl url = request.url();
    EXPECT_EQ(location.toStdString(), url.toString().toStdString());
}

TEST(NetworkAccessManager, CanAddCustomHeader)
{
    QtStageWebView webview;
    webview.continueLoad();
    NetworkAccessManager* manager = dynamic_cast<NetworkAccessManager*>(webview.page()->networkAccessManager());
    QString key = QString("MyHeaderKey");
    QString value = QString("MyHeaderValue");

    manager->addCustomHeader(key, value);
    QMap<QString, QString> headers = manager->getCustomHeaders();

    QList<QString> expectedKeys;
    expectedKeys << key;
    QList<QString> expectedValues;
    expectedValues << value;

    EXPECT_EQ(headers.keys(), expectedKeys);
    EXPECT_EQ(headers.values(), expectedValues);
}

TEST(NetworkAccessManager, CanClearCustomHeader)
{
    QtStageWebView webview;
    webview.continueLoad();
    NetworkAccessManager* manager = dynamic_cast<NetworkAccessManager*>(webview.page()->networkAccessManager());
    QString key = QString("MyHeaderKey");
    QString value = QString("MyHeaderValue");

    manager->addCustomHeader(key, value);
    manager->clearCustomHeaders();
    QMap<QString, QString> headers = manager->getCustomHeaders();

    QList<QString> expectedKeys;
    QList<QString> expectedValues;

    EXPECT_EQ(headers.keys(), expectedKeys);
    EXPECT_EQ(headers.values(), expectedValues);
}


