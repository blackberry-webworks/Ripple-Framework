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

#include "ProxyDialog.h"

using namespace BlackBerry::Ripple;

bool ProxyDialog::_didLogin = false;
QString ProxyDialog::_username;
QString ProxyDialog::_password;

ProxyDialog::ProxyDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Proxy Login");
    setModal(true);

    QGridLayout *layout = new QGridLayout(this);

    _editUsername = new QLineEdit(this);
    _editPassword = new QLineEdit(this);
    _editPassword->setEchoMode(QLineEdit::Password);

    _labelUsername = new QLabel(this);
    _labelPassword = new QLabel(this);
    _labelUsername->setText("Username");
    _labelUsername->setBuddy(_editUsername);
    _labelPassword->setText("Password");
    _labelPassword->setBuddy(_editPassword);

    _buttons = new QDialogButtonBox(this);
    _buttons->addButton(QDialogButtonBox::Ok);
    _buttons->addButton(QDialogButtonBox::Cancel);
    _buttons->button(QDialogButtonBox::Ok)->setText("Login");
    _buttons->button(QDialogButtonBox::Cancel)->setText("Cancel");

    connect(_buttons->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(close()));
    connect(_buttons->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(slotAcceptLogin()));

    layout->addWidget(_labelUsername, 0, 0);
    layout->addWidget(_editUsername, 0, 1);
    layout->addWidget(_labelPassword, 1, 0);
    layout->addWidget(_editPassword, 1, 1);
    layout->addWidget(_buttons, 2, 0, 1, 2);

    setLayout(layout);

}

ProxyDialog::~ProxyDialog()
{
}

void ProxyDialog::close()
{
	_didLogin = true;
}

void ProxyDialog::slotAcceptLogin()
{
	_username = _editUsername->text();
	_password = _editPassword->text();
	close();
}

bool ProxyDialog::didLogin()
{
	return _didLogin;
}

QString ProxyDialog::username()
{
	return _username;
}

QString ProxyDialog::password()
{
    return _password;
}
