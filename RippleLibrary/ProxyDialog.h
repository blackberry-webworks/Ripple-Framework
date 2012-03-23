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

#ifndef PROXYDIALOG_H_
#define PROXYDIALOG_H_

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QStringList>
#include <QDebug>

namespace BlackBerry
{
namespace Ripple
{

class ProxyDialog: public QDialog
{
    Q_OBJECT
private:
    QLabel *_labelUsername;
    QLabel *_labelPassword;
    QLineEdit *_editUsername;
    QLineEdit *_editPassword;
    QDialogButtonBox *_buttons;

    static bool _didLogin;
    static QString _username;
    static QString _password;

public:
    explicit ProxyDialog(QWidget *parent);
    ~ProxyDialog();
    static bool didLogin();
    static QString username();
    static QString password();

signals:
    void acceptLogin(QString& username, QString& password);

public slots:
    void slotAcceptLogin();
    void close();
};

}
}

#endif /* PROXYDIALOG_H_ */
