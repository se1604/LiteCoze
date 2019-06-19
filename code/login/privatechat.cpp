#include "privatechat.h"
#include "searchui.h"
#include "netizen.h"
#include "client.h"

PrivateChat *PrivateChat::_instance = nullptr;
extern Netizen * netizen;

using namespace std;

PrivateChat::PrivateChat()
{

}

PrivateChat *PrivateChat::getInstance()
{
    if(_instance == nullptr)
      _instance = new PrivateChat();
    return _instance;
}

void PrivateChat::selectFriend(long friendID)
{
    netizen->selectFriend(friendID);
}

void PrivateChat::findNetizen(long id)
{
    auto f = new Netizen(id);
    Client::getInstance()->send(f->toJson());
}

void PrivateChat::addFriend(long id)
{
    auto f = new Netizen(id);
    f->setConversionType(7);
    Client::getInstance()->send(f->toJson());
}

void PrivateChat::acceptAddFriendRequest(Netizen *f)
{
    f->setConversionType(8);
    Client::getInstance()->send(f->toJson());
}

void PrivateChat::showFindInfo(QString nickName, long id)
{
    emit _searchUI->showFindInfo(nickName, QString::number(id, 10));
}

void PrivateChat::startSearchUI()
{
    emit _searchUI->showSearchUI();
}

SearchUi *PrivateChat::getSearchUI() const
{
    return _searchUI;
}

void PrivateChat::setSearchUI(SearchUi *searchUI)
{
    _searchUI = searchUI;
}
