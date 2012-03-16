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

#include "ProxyConfig.h"
#include <QStringList>
#ifdef Q_WS_WIN
#include <windows.h>
#include <winhttp.h>
#endif
#ifdef Q_WS_MAC
#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SystemConfiguration.h>
#endif

using namespace BlackBerry::Ripple;

QString ProxyConfig::_proxyHost;
QString ProxyConfig::_proxyPort;

#ifdef Q_WS_WIN
void ProxyConfig::getProxySettingsWin()
{
	WINHTTP_PROXY_INFO proxyConfig;
	WinHttpGetDefaultProxyConfiguration(&proxyConfig);
	QString proxy = QString::fromWCharArray(proxyConfig.lpszProxy);
    _proxyHost = proxy.split(":")[0];
	_proxyPort = proxy.split(":")[1];
}
#endif

#ifdef Q_WS_MAC
void ProxyConfig::getProxySettingsMac()
{
    CFDictionaryRef proxyDict;

    CFNumberRef enableNum;
    int enable = 0;
    CFStringRef hostStr;
    char host[4096];
    CFNumberRef portNum = 0;
    int port;

    // Get the Proxy settings dictionary.
	proxyDict = SCDynamicStoreCopyProxies(NULL);

    if (proxyDict != NULL)
    {
    	// Get "enable" flag
        enableNum = (CFNumberRef) CFDictionaryGetValue(proxyDict, kSCPropNetProxiesHTTPEnable);
        if (enableNum != NULL)
        {
        	CFNumberGetValue(enableNum, kCFNumberIntType, &enable);
        }

        if (enable != 0)
        {
        	// Get proxy host
			hostStr = (CFStringRef) CFDictionaryGetValue(proxyDict,	kSCPropNetProxiesHTTPProxy);
			if (hostStr != NULL)
			{
				CFStringGetCString(hostStr, host, (CFIndex) 4096, kCFStringEncodingASCII);
			}

        	// Get proxy port
        	portNum = (CFNumberRef)	CFDictionaryGetValue(proxyDict,	kSCPropNetProxiesHTTPPort);
        	if (portNum != NULL)
        	{
        		CFNumberGetValue(portNum, kCFNumberIntType, &port);
        	}
        }

        CFRelease(proxyDict);
    }

    if (enable != 0)
    {
    	_proxyHost = host;
    	_proxyPort = port;
    }
    else
    {
		_proxyHost = "";
		_proxyPort = "";
    }
}
#endif

ProxyConfig::ProxyConfig()
{
#ifdef Q_WS_WIN
	getProxySettingsWin();
#endif
#ifdef Q_WS_MAC
	getProxySettingsMac();
#endif
}

ProxyConfig::~ProxyConfig()
{

}

QString ProxyConfig::proxyHost()
{
	return _proxyHost;
}

QString ProxyConfig::proxyPort()
{
	return _proxyPort;
}
