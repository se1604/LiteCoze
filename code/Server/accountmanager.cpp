#include "accountmanager.h"
#include "netizen.h"
#include <iostream>


using namespace std;
AccountManager* AccountManager::_instance = nullptr;

AccountManager::AccountManager()
{

}

void AccountManager::addNetizen(Netizen *n)
{
    _netizens.push_back(n);
}

void AccountManager::initFriend()
{
    for (auto n:_netizens) {
        DBBroker::getInstance()->initFrinedInfo(n);
    }
}

void AccountManager::initGroup()
{
    for(auto n:_netizens){
        DBBroker::getInstance()->initGroupInfo(n);
    }
}

Netizen *AccountManager::getNetizen(long id)
{
    for(auto n:_netizens){
        if(n->id()==id){
            return n;
        }
    }
    return nullptr;
}


AccountManager *AccountManager::getInstance()
{
    if(_instance == nullptr)
        _instance = new AccountManager();
    return _instance;
}
Netizen* AccountManager::checkAccount(Netizen *netizen, NetworkTransmission* networkTransmission)
{
    for(auto n : _netizens){
        if(n->checkAccount(netizen, networkTransmission)){
            return n;
        }
    }
    return nullptr;
}

Netizen* AccountManager::findNetizen(Netizen *netizen)
{
    for(auto n : _netizens){
        if(n->findNetizen(netizen)){
            return n;
        }
    }
    return nullptr;
}

void AccountManager::printInfo()
{
    cout << "所有的用户信息: " << endl;
    for(auto n : _netizens){
        n->printInfo();
    }
    cout << endl;
}
