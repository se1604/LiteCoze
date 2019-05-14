#include "privatechatroom.h"
#include <iostream>
#include "message.h"
#include "netizen.h"
#include "network.h"
using namespace std;

PrivateChatRoom::PrivateChatRoom(long id, Netizen *netizen1, Netizen *netizen2):
    m_id{id}, _netizen1{netizen1}, _netizen2{netizen2} {}

void PrivateChatRoom::addMessage(Message *msg)
{
    _messages.push_back(msg);
    if(msg->m_senderID == _netizen1->m_id)
    {
        if(_netizen2->_network != nullptr)
        {
            if(_netizen2->_network->socketIsOpen())
            {
                _netizen2->_network->write(msg->r_conversion);
            }
        }
        else{
            _offlineMessages.push_back(msg);
        }
    }
    if(msg->m_senderID == _netizen2->m_id){
        if(_netizen1->_network != nullptr){
            if(_netizen1->_network->socketIsOpen()){
                _netizen1->_network->write(msg->r_conversion);
            }
        }
        else{
            _offlineMessages.push_back(msg);
        }
    }
    //_unsendMessages.push_back(msg);
}

void PrivateChatRoom::sendOfflineMessages(Netizen *netizen)
{
    while(!(_offlineMessages.empty())){
        netizen->_network->write(_offlineMessages.front()->r_conversion);
        _offlineMessages.pop_front();
    }
}

long PrivateChatRoom::id() const
{
    return m_id;
}

void PrivateChatRoom::printInfo()
{
    for(auto msg : _messages){
        cout << msg->m_content;
    }
    cout << endl;
}
