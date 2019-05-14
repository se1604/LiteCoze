#include "manager.h"
#include "netizen.h"
#include "network.h"
#include <iostream>

#include "network.h"

using namespace std;

Manager* Manager::_instance = nullptr;

Manager::Manager()
{

}


Manager *Manager::getInstance()
{
    if(_instance == nullptr)
        _instance = new Manager();
    return _instance;
}

void Manager::addNetizen(Netizen *n)
{
    //_netizens->push_back(n);
    _netizens.push_back(n);
}

void Manager::addPrivateChatRoom(PrivateChatRoom *pcr)
{
    _privateChatRooms.push_back(pcr);
}

void Manager::setNetizenSocket(Network *network, Netizen *netizen)
{
    for(auto n : _netizens){
        if(n->m_id == netizen->m_id){
            n->_network = network;
            network->_netizen = n;
        }
    }
}



void Manager::printInfo()
{
    cout << "所有的用户信息: " << endl;
    for(auto n : _netizens){
        cout << "id: " << n->m_id << "昵称: " << n->m_nickname << endl;
    }
    cout << endl;
}
