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

#include "stdafx.h"
#include "QtStageWebView.h"
#include "BlackBerryBus.h"

using namespace BlackBerry::Starbuck;

QtStageWebView::QtStageWebView(QWidget *p) : QWebView(p), waitForJsLoad(true)
{	
    //Turn off context menu's (i.e. menu when right clicking, you will need to uncommment this if you want to use web inspector,
    //there is currently a conflict between the context menus when using two QWebView's
    //this->setContextMenuPolicy(Qt::NoContextMenu);

	// Connect signals for events
	connect(this, SIGNAL(urlChanged(const QUrl&)), this, SLOT(notifyUrlChanged(const QUrl&)));

	if (page() && page()->mainFrame())
    {
        connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(notifyJavaScriptWindowObjectCleared()));
    }

	//enable web inspector
	this->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
}

QtStageWebView::~QtStageWebView(void)
{
}

void QtStageWebView::setTraits(const QVariantMap& settings)
{
	if (settings.contains("windowGeometry"))
	{
		QVariantMap window_geometry = settings.value("windowGeometry").toMap();
		
		if (window_geometry.contains("x") && window_geometry.contains("y") &&
			window_geometry.contains("w") && window_geometry.contains("h"))
		{
			setWindowGeometry(	window_geometry.value("x").toInt(), window_geometry.value("y").toInt(),
								window_geometry.value("w").toInt(), window_geometry.value("h").toInt());
		}
	}

	if (settings.contains("visible"))
	{
		visible(settings.value("visible").toBool());
	}

	// We should always process this before loading the url.
	if (settings.contains("crossOrigin"))
	{
		enableCrossSiteXHR(settings.value("crossOrigin").toBool());
	}

	// We should always process this before loading the url.
	if (settings.contains("customHTTPHeaders"))
	{
		// The customHTTPHeaders are stored as an array of key/value pairs.  We must
		// first convert the array into a QVariantList.  For each item in the list,
		// we convert the key/value object into a QVariantMap.  We then retrieve the
		// key and value strings from the map.

		QVariantList custom_headers = settings.value("customHTTPHeaders").toList();
				
		if (custom_headers.size())
		{
			QStringList headers_list;

			for (int i = 0; i < custom_headers.size(); i++)
			{
				QVariantMap header = custom_headers.at(i).toMap();

				if (header.contains("key") && header.contains("value"))
				{
					headers_list.append(header.value("key").toString());
					headers_list.append(header.value("value").toString());
				}
			}

			customHTTPHeaders(headers_list);
		}
	}

	if (settings.contains("URL"))
	{
		loadURL(settings.value("URL").toString());
	}
}

void QtStageWebView::loadURL(QString url)
{
	QNetworkRequest request(url);

	//Add custom headers
	for (int i = 0; i + 1 < _headers.size(); i += 2)
	{
		QByteArray key = _headers.at(i).toAscii();
		QByteArray value = _headers.at(i + 1).toAscii();
		request.setRawHeader(key, value);
	}

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

  if (waitForJsLoad)
      loop.exec();
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

QStringList& QtStageWebView::customHTTPHeaders()
{
	return _headers;
}

void QtStageWebView::customHTTPHeaders(const QStringList& headers)
{
	_headers.clear();
	_headers = headers;
}

void QtStageWebView::customHTTPHeaders(QString key, QString value)
{
	QStringList headers_list;
	headers_list.append(key);
	headers_list.append(value);
	
	customHTTPHeaders(headers_list);
}

void QtStageWebView::visible(bool enable)
{
	if (this->isVisible() == enable)
		return;

	(enable) ? this->show():this->hide();
}
