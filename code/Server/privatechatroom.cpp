#include "privatechatroom.h"
#include "netizen.h"
#include "message.h"
#include <iostream>
using namespace std;

PrivateChatRoom::PrivateChatRoom(long id, Netizen *netizen1, Netizen *netizen2):m_id{id}, _netizen1{netizen1}, _netizen2{netizen2}
{

}

Netizen* PrivateChatRoom::getFriend(Netizen *netizen)
{
    if(netizen == _netizen1){
        return _netizen2;
    } else if (netizen == _netizen2) {
        return _netizen1;
    }

}

long PrivateChatRoom::id() const
{
    return m_id;
}

void PrivateChatRoom::addMessage(Message* message){
    _messages.push_back(message);
    if(_netizen1->id() == message->senderID()){
        cout << "isOnLine: " << _netizen2->isOnLine() << endl;
        if(_netizen2->isOnLine()){
            _netizen2->sendMessage(message->toJson());
        } else {
            _netizen2OfflineMessages.push_back(message);
        }
    }
    if(_netizen2->id() == message->senderID()){
        cout << "isOnLine: " << _netizen1->isOnLine() << endl;
        if(_netizen1->isOnLine()){
            _netizen1->sendMessage(message->toJson());
        } else {
            _netizen1OfflineMessages.push_back(message);
        }
    }
}

void PrivateChatRoom::sendAllOffLineMessages(Netizen *netizen)
{
    if(netizen->id() == _netizen1->id()){
        cout << "length: " << _netizen1OfflineMessages.size() << endl;
        while(!(_netizen1OfflineMessages.empty())){
            netizen->sendMessage(_netizen1OfflineMessages.front()->toJson());
            _netizen1OfflineMessages.pop_front();
        }
    } else{
        cout << "length: " << _netizen2OfflineMessages.size() << endl;
        while(!(_netizen2OfflineMessages.empty())){
            netizen->sendMessage(_netizen2OfflineMessages.front()->toJson());
            _netizen2OfflineMessages.pop_front();
        }
    }

}
