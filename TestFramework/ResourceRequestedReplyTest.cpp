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

#include "ResourceRequestedReplyTest.h"

TEST(ResourceRequestedReply, CanRespond)
{
    const QString RESPONSETEXT = "responseText";
    const QString CODE = "code";

    QString id("100");
    QString strurl("www.google.com");
    QUrl url(strurl);
    ResourceRequestedReply reply(id, url);
    //Test construct
    EXPECT_EQ(id, reply.getID());
    EXPECT_EQ(strurl, reply.url().toString());
    EXPECT_EQ(false, reply.isSubstitute());

    //response deny
    QVariantMap deny;
    deny.insert(RESPONSETEXT, QVariant("deny"));
    reply.respond(deny);
    EXPECT_EQ(QVariant(403), reply.attribute(QNetworkRequest::HttpStatusCodeAttribute));

    //response substitute
    deny[RESPONSETEXT] = QVariant("substitute");
    reply.respond(deny);
    EXPECT_EQ(true, reply.isSubstitute());

    //custom respose with code and msg
    QVariant msg("hello world");
    deny[RESPONSETEXT] = msg;
    QVariant code("200");
    deny.insert(CODE, code);
    reply.respond(deny);
    EXPECT_EQ(code, reply.attribute(QNetworkRequest::HttpStatusCodeAttribute));
    QVariant actual(reply.readAll());
    EXPECT_EQ(msg, actual);
}

