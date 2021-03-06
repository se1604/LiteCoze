#include "searchui.h"
#include "client.h"
#include "privatechat.h"
#include "groupchat.h"
#include "netizen.h"

extern Netizen * netizen;

SearchUi::SearchUi()
{
    Client::getInstance()->setSearchUI(this);
    GroupChat::getInstance()->setSearchUI(this);
    PrivateChat::getInstance()->setSearchUI(this);
}

void SearchUi::findNetizen(QString id)
{
    Client::getInstance()->findNetizen(id.toLong());
}

void SearchUi::findGroup(QString id)
{
    Client::getInstance()->findGroup(id.toLong());
}

void SearchUi::addFriend(QString id)
{
    Client::getInstance()->addFriend(id.toLong());
}

void SearchUi::addGroup(QString roomid)
{
    Client::getInstance()->addGroup(netizen->id(),roomid.toLong());
}
