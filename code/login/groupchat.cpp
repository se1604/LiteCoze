#include "groupchat.h"
#include "searchui.h"
#include "netizen.h"
#include "client.h"
#include "clientui.h"

GroupChat *GroupChat::_instance = nullptr;
extern Netizen * netizen;

using namespace std;

GroupChat::GroupChat()
{

}

ClientUI *GroupChat::getClientUI() const
{
    return _clientUI;
}

void GroupChat::setClientUI(ClientUI *clientUI)
{
    _clientUI = clientUI;
}

void GroupChat::showGrouplistInfo(QString name, QString roomid)
{
    emit _clientUI->showGrouplistInfo(name, roomid, QString::number(netizen->id(), 10));
}

void GroupChat::showGroupMsg(QString id, QString msg, QString roomid)
{
    emit _clientUI->showGroupMsg(id, QString::fromStdString(netizen->sendername(roomid.toLong(), id.toLong())), msg, roomid);
}

void GroupChat::showFindGroupInfo(QString name, QString id)
{
    emit _searchUI->showFindGroupInfo(name, id);
}

void GroupChat::showNewGroupInfo(QString name, QString id, QString groupName, QString roomid)
{
    emit _clientUI->showNewGroupInfo(name, id, groupName, roomid);
}

void GroupChat::addInGroup(long roomid, long netizenid)
{
    netizen->addInGroup(roomid, netizenid);
}

SearchUi *GroupChat::getSearchUI() const
{
    return _searchUI;
}

void GroupChat::setSearchUI(SearchUi *searchUI)
{
    _searchUI = searchUI;
}

GroupChat *GroupChat::getInstance()
{
    if(_instance == nullptr)
        _instance = new GroupChat();
    return _instance;
}
