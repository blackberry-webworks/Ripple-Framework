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
#include "QtStageWebView.h"
#include "BlackBerryBus.h"
#include "WebViewEventHandler.h"

using namespace BlackBerry::Starbuck;

QtStageWebView::QtStageWebView(QWidget *p) : QWebView(p), 
     waitForJsLoad(true),
     m_lastContentPos(0,0), 
     m_nextScrollStepLength(0,0), 
     m_eventHandler(new NormalEventHandler(this))
{	
    //Turn off context menu's (i.e. menu when right clicking)
	//this->setContextMenuPolicy(Qt::NoContextMenu);

	// Connect signals for events
	connect(this, SIGNAL(urlChanged(const QUrl&)), this, SLOT(notifyUrlChanged(const QUrl&)));
  connect(&m_scrollTimer, SIGNAL(timeout()), this, SLOT(animateScroll()));

	if (page() && page()->mainFrame())
    {
        connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(notifyJavaScriptWindowObjectCleared()));
    }

	//Initialize headers to 0
	_headersSize = 0;

	//enable web inspector
	this->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
}

QtStageWebView::~QtStageWebView(void)
{
}

void QtStageWebView::loadURL(QString url)
{
	QNetworkRequest request(url);

	//Add custom headers
	for (unsigned int i = 0; i + 1 < _headersSize; i += 2)
		request.setRawHeader(_headers[i], _headers[i + 1]);

	load(request);
}

void QtStageWebView::reload()
{
	QWebView::reload();
}

void QtStageWebView::notifyUrlChanged(const QUrl& url)
{
	emit urlChanged(url.toString());
}

void QtStageWebView::notifyJavaScriptWindowObjectCleared()
{
  registerEventbus();
  QEventLoop loop;
  QObject::connect(this, SIGNAL(jsLoaded()), &loop, SLOT(quit()));
	emit javaScriptWindowObjectCleared();
  if ( waitForJsLoad )
  {
    loop.exec();
  }
}

void QtStageWebView::registerEventbus()
{
  QWebFrame* frame = page()->mainFrame();
  frame->addToJavaScriptWindowObject(QString("eventbus2"), new BlackBerryBus(this, frame));
  frame->evaluateJavaScript(BlackBerry::Starbuck::eventbusSource);

  // check for iframes, if found add to window object
  for(int i = 0; i < frame->childFrames().length(); i++)
  {
      frame->childFrames()[i]->addToJavaScriptWindowObject(QString("eventbus2"), new BlackBerryBus(this, frame->childFrames()[i]));
      frame->childFrames()[i]->evaluateJavaScript(BlackBerry::Starbuck::eventbusSource);
  }
}

void QtStageWebView::continueLoad()
{
  emit jsLoaded();
  waitForJsLoad = false;
}


bool QtStageWebView::enableCrossSiteXHR()
{
	return this->settings()->testAttribute(QWebSettings::LocalContentCanAccessRemoteUrls);
}

void QtStageWebView::enableCrossSiteXHR(bool xhr)
{
   return this->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, xhr);
}

QVariant QtStageWebView::executeJavaScript(QString script)
{
	return page()->mainFrame()->evaluateJavaScript(script);
}

QString QtStageWebView::location()
{
	return url().toString();
}

bool QtStageWebView::isHistoryBackEnabled()
{
	return history() ? history()->canGoBack() : false;
}

bool QtStageWebView::isHistoryForwardEnabled()
{
	return history() ? history()->canGoForward() : false;
}

void QtStageWebView::historyBack()
{
	back();
}

void QtStageWebView::historyForward()
{
	forward();
}

int QtStageWebView::historyLength()
{
	return history() ? history()->count() : 0;
}

int QtStageWebView::historyPosition()
{
	return history() ? history()->currentItemIndex() : -1;
}

void QtStageWebView::historyPosition(int position)
{
	if (history() && position >= 0 && position < history()->count())
	{
		history()->goToItem(history()->itemAt(position));
	}
}

char** QtStageWebView::customHTTPHeaders()
{
	return _headers;
}

void QtStageWebView::customHTTPHeaders(char *headers[], unsigned int headersSize)
{
	_headers = new char*[headersSize];
	
	for (unsigned int i = 0; i < headersSize; i++){
        _headers[i] = new char[strlen(headers[i]) + 1];
		strcpy(_headers[i], headers[i]);
	}

	_headersSize = headersSize;
}

void QtStageWebView::customHTTPHeaders(QString key, QString value)
{
	QByteArray mKey = key.toAscii();
	QByteArray mValue = value.toAscii();
	char *headersArray[2];
	headersArray[0] = mKey.data();
	headersArray[1] = mValue.data();
	customHTTPHeaders( headersArray, 2);
}

void QtStageWebView::visible(bool enable)
{
	if (this->isVisible() == enable)
		return;

	(enable)? this->show():this->hide();
}

///////////////////////////////////////////////////////////////////////////////////
//touch scrolling implementation
QPoint QtStageWebView::scrollPosition()
{
    return page()->mainFrame()->scrollPosition();
}

void QtStageWebView::scrollPosition(QPoint pos)
{
    page()->mainFrame()->setScrollPosition(pos);
}

void QtStageWebView::mousePressEvent(QMouseEvent* e)
{
  Q_ASSERT(m_eventHandler);
  m_eventHandler->mousePressEvent(e);
}

void QtStageWebView::mouseReleaseEvent(QMouseEvent* e)
{
  Q_ASSERT(m_eventHandler);
  m_eventHandler->mouseReleaseEvent(e);
}
 
void QtStageWebView::mouseMoveEvent(QMouseEvent* e)
{
  Q_ASSERT(m_eventHandler);
  m_eventHandler->mouseMoveEvent(e);
}

void QtStageWebView::mouseDoubleClickEvent(QMouseEvent* ev)
{
  //QWebView::mouseDoubleClickEvent(ev);
  Q_ASSERT(m_eventHandler);
  m_eventHandler->mouseDoubleClickEvent(ev);
}

QPoint QtStageWebView::validateScrollPoint(const QPoint& point)
{
    QSize contentSize = page()->mainFrame()->contentsSize();
    QPoint p(point);
    if (p.x() < 0)
        p.setX(0);
    if (p.y() < 0)
        p.setY(0);

    if (p.x() > contentSize.width() - width())
        p.setX(contentSize.width() - width());
    if (p.y() > contentSize.height() - height())
        p.setY(contentSize.height() - height());
    return p;
}

void QtStageWebView::animateScroll()
{
    // This value is larger, the scrolling speed drops faster:
    const static int ScrollAnimationInertia = 5;

    if (m_nextScrollStepLength.isNull()) {
        m_scrollTimer.stop();
        return;
    }

    QPoint newPoint = m_lastContentPos + m_nextScrollStepLength;
    QPoint vPoint = validateScrollPoint(newPoint);
    if (m_lastContentPos == vPoint) {
        m_scrollTimer.stop();
        return;
    }

    QPoint delta = m_lastContentPos - vPoint;
    scrollBy(delta.x(), delta.y());
    m_lastContentPos = vPoint;
    m_nextScrollStepLength = QPoint(qMax(qAbs(m_nextScrollStepLength.x()) - ScrollAnimationInertia, 0) * (m_nextScrollStepLength.x() < 0 ? -1 : 1),
        qMax(qAbs(m_nextScrollStepLength.y()) - ScrollAnimationInertia, 0) * (m_nextScrollStepLength.y() < 0 ? -1 : 1));

    if (newPoint.x() != vPoint.x() && newPoint.y() != vPoint.y())
        m_scrollTimer.stop();
}

void QtStageWebView::scrollBy(int deltaX, int deltaY)
{
    QPoint pos = scrollPosition();
    QSize contentSize = page()->mainFrame()->contentsSize();
    int maxScrollH = contentSize.width() - width();
    int maxScrollV = contentSize.height() - height();

    int x = pos.x() - deltaX;
    int y = pos.y() - deltaY;
    if (x > maxScrollH)
        x = maxScrollH;
    if (x < 0)
        x = 0;

    if (y > maxScrollV)
        y = maxScrollV;
    if (y < 0)
        y = 0;
    scrollPosition(QPoint(x, y));
}

void QtStageWebView::clearFocusNode()
{
    if ( page())
        page()->clearFocusNode();
}

void QtStageWebView::handleMouseEvent(QMouseEvent me)
{
   if ( page() )
       page()->handleMouseEvent(me);
}

bool QtStageWebView::scrollNodeRecursively(QWebFrame* subframe, QSize delta)
{
    return page()->scrollNodeRecursively(subframe, delta);
}

QPoint QtStageWebView::getFatFingerPos(QPoint& pos)
{
    if ( page() )
        return page()->getFatFingerPos(pos);
    return pos;
}

