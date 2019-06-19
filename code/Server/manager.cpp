#include "manager.h"
#include "netizen.h"
#include <iostream>

using namespace std;
Manager* Manager::_instance = nullptr;

Manager::Manager()
{

}

void Manager::addNetizen(Netizen *n)
{
    _netizens.push_back(n);
}

void Manager::initFriend()
{
    for (auto n:_netizens) {
        DBBroker::getInstance()->initFrinedInfo(n);
    }
}

Netizen *Manager::getNetizen(long id)
{
    for(auto n:_netizens){
        if(n->id()==id){
            return n;
        }
    }
    return nullptr;
}

Manager *Manager::getInstance()
{
    if(_instance == nullptr)
        _instance = new Manager();
    return _instance;
}

Netizen* Manager::checkAccount(Netizen *netizen, NetworkTransmission* networkTransmission)
{
    printInfo();
    for(auto n : _netizens){
        if(n->checkAccount(netizen, networkTransmission)){
            return n;
        }
    }
    return nullptr;
}

void Manager::printInfo()
{
    cout << "所有的用户信息: " << endl;
    for(auto n : _netizens){
        n->printInfo();
    }
    cout << endl;
}
