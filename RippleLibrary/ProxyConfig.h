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

#ifndef PROXYCONFIG_H_
#define PROXYCONFIG_H_

#include <QObject>
#include <QString>

namespace BlackBerry {
namespace Ripple {

class ProxyConfig : public QObject
{
	Q_OBJECT
public:
	ProxyConfig();
	~ProxyConfig();
#ifdef Q_WS_WIN
	void getProxySettingsWin();
#endif
#ifdef Q_WS_MAC
	void getProxySettingsMac();
#endif

	static QString _proxyHost;
	static QString _proxyPort;
	static QString proxyHost();
	static QString proxyPort();
};

}
}

#endif /* PROXYCONFIG_H_ */
