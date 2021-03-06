#include "clientui.h"
#include "client.h"

ClientUI *ClientUI::_instance = nullptr;

ClientUI::ClientUI()
{
    Client::getInstance()->setClientUI(this);
}

ClientUI *ClientUI::getInstance()
{
    if(_instance != nullptr)
        return _instance;
    _instance = new ClientUI();
    return _instance;
}


void ClientUI::selectFriend(QString friendID)
{
    Client::getInstance()->selectFriend(friendID.toLong());
}

void ClientUI::sendNewMessage(QString content)
{
    Client::getInstance()->sendNewMessage(content.toStdString());
}

QString ClientUI::id() const
{
    return m_id;
}

void ClientUI::setId(const QString &id)
{
    if(m_id != id)
    {
        m_id = id;
        emit idChanged();
    }
}
