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

#include "stdafx.h"
#include "RequestObject.h"

using namespace BlackBerry::Starbuck;

RequestObject::RequestObject(QString& url, QObject *parent, QWebFrame* frame) : QObject(parent), m_url(url), m_pWebFrame(frame)
{
}

RequestObject::~RequestObject()
{
}

void RequestObject::setUrl(QString& url)
{
    m_url = url;
}

void RequestObject::setWebFrame(QWebFrame* frame)
{
    m_pWebFrame = frame;
}

void RequestObject::allow()
{
    qDebug() << "allowed access: " << m_url;
    m_pWebFrame->setAllowAccess(true);
}

void RequestObject::deny()
{
    qDebug() << "denied access: " << m_url;
    m_pWebFrame->setAllowAccess(false);
}

void RequestObject::respond(int code, const QString& responseText)
{
    qDebug() << "respond to: " << m_url << "code: " << code << "respons text: " << responseText;
    m_pWebFrame->respond(code, responseText, m_url);
}

