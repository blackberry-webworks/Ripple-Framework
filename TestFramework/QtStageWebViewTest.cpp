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

#include "QtStageWebViewTest.h"

TEST(QtStageWebView, CanRetrieveEmptyLocation)
{
	QtStageWebView webview;
	webview.continueLoad();

	QString location("");
	
	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));

	webview.loadURL(location);
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();
	EXPECT_EQ(location.toStdString(), webview.location().toStdString());
}

TEST(QtStageWebView, CanRetrieveValidLocation)
{
	QtStageWebView webview;
	webview.continueLoad();

	QString location("http://www.google.ca/");

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));

	webview.loadURL(location);
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();
	EXPECT_EQ(location.toStdString(), webview.location().toStdString());
}

TEST(QtStageWebView, CannotGoBackWhenOnePageLoaded)
{
	QtStageWebView webview;
	webview.continueLoad();

	QString location("http://www.google.ca/");

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));

	webview.loadURL(location);
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();
	EXPECT_EQ(location.toStdString(), webview.location().toStdString());

	EXPECT_FALSE(webview.isHistoryBackEnabled());
}

TEST(QtStageWebView, CanGoBackWhenMultiplePagesLoaded)
{
	QtStageWebView webview;
	webview.continueLoad();

	QString location_0("http://www.google.ca/");
	QString location_1("http://www.thestar.com/mobile");
	
	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));
 
	// Create a timer to ensure the event loop quits
	QTimer timer;
	QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

	webview.loadURL(location_0);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_0.toStdString(), webview.location().toStdString());

	webview.loadURL(location_1);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_1.toStdString(), webview.location().toStdString());

	EXPECT_TRUE(webview.isHistoryBackEnabled());
	webview.historyBack();
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_0.toStdString(), webview.location().toStdString());
}

TEST(QtStageWebView, CannotGoForwardWhenOnePageLoaded)
{
	QtStageWebView webview;
	webview.continueLoad();

	QString location_0("http://www.thestar.com/mobile");

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));

	webview.loadURL(location_0);
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();
	EXPECT_EQ(location_0.toStdString(), webview.location().toStdString());

	EXPECT_FALSE(webview.isHistoryForwardEnabled());
}

TEST(QtStageWebView, CanGoForwardWhenMultiplePagesLoaded)
{
	QtStageWebView webview;
	webview.continueLoad();

	QString location_0("http://www.thestar.com/mobile");
	QString location_1("http://www.google.ca/");
	
	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));

	// Create a timer to ensure the event loop quits
	QTimer timer;
	QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

	webview.loadURL(location_0);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_0.toStdString(), webview.location().toStdString());

	webview.loadURL(location_1);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_1.toStdString(), webview.location().toStdString());

	EXPECT_TRUE(webview.isHistoryBackEnabled());
	webview.historyBack();
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_0.toStdString(), webview.location().toStdString());

	EXPECT_TRUE(webview.isHistoryForwardEnabled());
	webview.historyForward();
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_1.toStdString(), webview.location().toStdString());
}

TEST(QtStageWebView, CanRetrieveHistoryLength)
{
	QtStageWebView webview;
	webview.continueLoad();

	QString location_0("http://www.thestar.com/mobile");
	QString location_1("http://www.google.ca/");

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));

	QTimer timer;
	QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

	webview.loadURL(location_0);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(1, webview.historyLength());

	webview.loadURL(location_1);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(2, webview.historyLength());
}

TEST(QtStageWebView, CanRetrieveHistoryPosition)
{
	QtStageWebView webview;
	webview.continueLoad();

	QString location_0("http://www.thestar.com/mobile");
	QString location_1("http://www.google.ca/");
	QString location_2("http://www.wikipedia.org/");
	
	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));

	QTimer timer;
	QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

	webview.loadURL(location_0);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(0, webview.historyPosition());

	webview.loadURL(location_1);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(1, webview.historyPosition());

	webview.loadURL(location_2);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(2, webview.historyPosition());

	EXPECT_TRUE(webview.isHistoryBackEnabled());
	webview.historyBack();
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(1, webview.historyPosition());
}

TEST(QtStageWebView, CanGoToSpecificHistoryLocation)
{
	QtStageWebView webview;
	webview.continueLoad();

	QString location_0("http://www.thestar.com/mobile");
	QString location_1("http://www.google.ca/");
	QString location_2("http://www.wikipedia.org/");
	QString location_3("http://www.thestar.com/mobile");

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));
	
	QTimer timer;
	QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

	webview.loadURL(location_0);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_0.toStdString(), webview.location().toStdString());
	EXPECT_EQ(0, webview.historyPosition());

	webview.loadURL(location_1);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_1.toStdString(), webview.location().toStdString());
	EXPECT_EQ(1, webview.historyPosition());

	webview.loadURL(location_2);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_2.toStdString(), webview.location().toStdString());
	EXPECT_EQ(2, webview.historyPosition());

	webview.loadURL(location_3);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_3.toStdString(), webview.location().toStdString());
	EXPECT_EQ(3, webview.historyPosition());

	webview.historyPosition(1);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_1.toStdString(), webview.location().toStdString());
	EXPECT_EQ(1, webview.historyPosition());
}

TEST (QtStageWebView, CanSetVisable){
	QtStageWebView webview;
	webview.continueLoad();

	webview.loadURL("http://www.google.ca/");
	
	webview.visible(true);
	EXPECT_TRUE(webview.isVisible());
}

TEST (QtStageWebView, CanSetInvisable){
	QtStageWebView webview;
	webview.continueLoad();

	webview.loadURL("http://www.google.ca/");

	webview.visible(false);
	EXPECT_FALSE(webview.isVisible());
}

TEST (QtStageWebView, CanAddCustomHeader){
	QtStageWebView webview;

	QString key = "MyHeaderKey";
	QString value = "MyHeaderValue";

	webview.customHTTPHeaders(key, value);

	QStringList return_array = webview.customHTTPHeaders();
	EXPECT_EQ(key.toStdString(), return_array.at(0).toStdString());
	EXPECT_EQ(value.toStdString(), return_array.at(1).toStdString());
}

TEST (QtStageWebView, CanAddCustomHeaderArray){
	QtStageWebView webview;

	QStringList headers_array;
	headers_array.append("MyHeaderKey");
	headers_array.append("MyHeaderValue");
	
	webview.customHTTPHeaders(headers_array);
	QStringList return_array = webview.customHTTPHeaders();
	
	EXPECT_EQ(headers_array.at(0).toStdString(), return_array.at(0).toStdString());
	EXPECT_EQ(headers_array.at(1).toStdString(), return_array.at(1).toStdString());
}

TEST(QtStageWebView, CanEnableCrossOrigin)
{
	QtStageWebView webview;
	webview.continueLoad();

	webview.loadURL("http://www.google.ca");

	webview.enableCrossSiteXHR(true);
	EXPECT_TRUE(webview.enableCrossSiteXHR());
}

TEST(QtStageWebView, CanDisableCrossOrigin)
{
	QtStageWebView webview;
	webview.continueLoad();

	webview.loadURL("http://www.google.ca");

	webview.enableCrossSiteXHR(false);
	EXPECT_FALSE(webview.enableCrossSiteXHR());
}

TEST(QtStageWebView, CanExecuteJavaScript)
{
	QtStageWebView webview;
	webview.continueLoad();

	webview.loadURL("http://www.google.ca");

	EXPECT_EQ(7, webview.executeJavaScript("a=3+4").toInt());
}

TEST (QtStageWebView, CanSignalUrlChanged){
	QtStageWebView webview;
	webview.continueLoad();

	QString location("http://www.google.ca/");

	QSignalSpy spy(&webview, SIGNAL(urlChanged(QString)));

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));

	webview.loadURL(location);
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();
	
	ASSERT_EQ(1, spy.count());
	QList<QVariant> arguments = spy.takeFirst();
	QString sent_url = qvariant_cast<QString>(arguments.at(0));
	EXPECT_EQ(location.toStdString(), sent_url.toStdString());
}

TEST(QtStageWebView, CanSignalJavaScriptWindowCleared)
{
	QtStageWebView webview;
	webview.continueLoad();

	QString location("http://www.google.ca/");

	QSignalSpy spy(&webview, SIGNAL(javaScriptWindowObjectCleared()));
		
	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));

	webview.loadURL(location);
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();

	EXPECT_EQ(1, spy.count());
}

TEST(QtStageWebView, CanReloadPage)
{
	QtStageWebView webview;
	webview.continueLoad();

    // Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));

	webview.loadURL("http://www.google.ca");
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();

    // Change the document title, this should get reset when we reload the page
    webview.executeJavaScript("document.title = 'testing'");

    webview.reload();
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();

    QVariant result = webview.executeJavaScript("document.title");

	EXPECT_NE(result.toString().toStdString(), "testing");
}

TEST(QtStageWebView, CanSetMultipleTraits)
{
	QtStageWebView webview;
	webview.continueLoad();

	// Setting up the window geometry
	QRect window_rect(200, 100, 360, 480);
	QVariantMap window_geometry;
	window_geometry.insert("x", window_rect.x());
	window_geometry.insert("y", window_rect.y());
	window_geometry.insert("w", window_rect.width());
	window_geometry.insert("h", window_rect.height());

	// Setting up the custom HTTP headers
	QString header_key("TestHeaderKey");
	QString header_value("TestHeaderValue");

	QVariantMap custom_header;
	custom_header.insert("key", header_key);
	custom_header.insert("value", header_value);

	QVariantList headers_list;
	headers_list.append(custom_header);

	// Setting up the URL
	QString location("http://www.google.ca/");

	// Add all settings to the QVariantMap/JSON object
	QVariantMap settings;
	settings.insert("windowGeometry", window_geometry);
	settings.insert("visible", false);
	settings.insert("URL", location);
	settings.insert("crossOrigin", true);
	settings.insert("customHTTPHeaders", headers_list);

	// Set up event loop to wait for loadFinished, since we will be loading a url
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));

	webview.setTraits(settings);
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();

	EXPECT_TRUE(webview.enableCrossSiteXHR());
	EXPECT_FALSE(webview.isVisible());
	EXPECT_EQ(location.toStdString(), webview.location().toStdString());
	EXPECT_EQ(window_rect, webview.geometry());
		
	QStringList return_array = webview.customHTTPHeaders();
	EXPECT_EQ(header_key.toStdString(), return_array.at(0).toStdString());
	EXPECT_EQ(header_value.toStdString(), return_array.at(1).toStdString());
}