#include "clientui.h"
#include "client.h"
#include "netizen.h"
#include "privatechat.h"
#include "groupchat.h"

ClientUI *ClientUI::_instance = nullptr;

ClientUI::ClientUI()
{
    Client::getInstance()->setClientUI(this);
    GroupChat::getInstance()->setClientUI(this);
    PrivateChat::getInstance()->setClientUI(this);
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

void ClientUI::startSearchUI()
{
    Client::getInstance()->startSearchUI();
}

void ClientUI::acceptAddFriendRequest(QString id, QString nickname)
{
    auto f = new Netizen(id.toLong(), nickname.toStdString(), 1);
    Client::getInstance()->acceptAddFriendRequest(f);
}

void ClientUI::acceptAddGroupRequest(QString id, QString name)
{
    auto f = new Netizen(id.toLong(), name.toStdString(), 1);
    Client::getInstance()->acceptAddGroupRequest(f);
}

void ClientUI::flushAccountInfo()
{
    Client::getInstance()->flushAccountInfo();
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
