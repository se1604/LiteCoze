#include "loginUI.h"
#include "client.h"
LogInUI::LogInUI()
{
    Client::getInstance()->setLogInUI(this);
}

void LogInUI::logIn(QString id, QString password)
{
    Client::getInstance()->logIn(id.toLong(), password.toStdString());

}

void LogInUI::startClientUI()
{
    Client::getInstance()->startClientUI();
}

void LogInUI::myRegister(QString id, QString nickname, QString password)
{
    Client::getInstance()->Register(id.toLong(), nickname.toStdString(), password.toStdString());
}
