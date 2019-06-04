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
    //_netizens->push_back(n);
    _netizens.push_back(n);
}
Manager *Manager::getInstance()
{
    if(_instance == nullptr)
        _instance = new Manager();
    return _instance;
}
Netizen* Manager::checkAccount(Netizen *netizen, NetworkTransmission* networkTransmission)
{
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
