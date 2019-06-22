#include "accountmanager.h"
#include "netizen.h"
#include <iostream>

#include "groupchatroom.h"

using namespace std;
AccountManager* AccountManager::_instance = nullptr;

AccountManager::AccountManager()
{

}

void AccountManager::addNetizen(Netizen *n)
{
    _netizens.push_back(n);
}

void AccountManager::addGroupChatroom(GroupChatroom *groupChatroom)
{
  //  cout << "_groupChatrooms:  " << groupChatroom->id() << endl;
    bool flag=true;
    if(_groupChatrooms.size()==0){
        _groupChatrooms.push_back(groupChatroom);
    }else{
        for (auto g:_groupChatrooms){
            if(g->id()==groupChatroom->id()){
                flag=false;
            }
        }
        if(flag==true){
            _groupChatrooms.push_back(groupChatroom);
        }
    }
//    for (auto g:_groupChatrooms){
//        if(g->id()==groupChatroom->id()){
//            return;
//        }
//    }
//    _groupChatrooms.push_back(groupChatroom);
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
        if(n->id() == netizen->id()){
            return n;
        }
    }
    return nullptr;
}

GroupChatroom *AccountManager::findGroupChatroom(GroupChatroom *groupChatroom)
{
    for(auto gcr : _groupChatrooms){
        if(gcr->id() == groupChatroom->id()){
            cout << "查找成功" << endl;
            return gcr;
        }
    }
    cout << "查找失败" << endl;
    return nullptr;
}

void AccountManager::printInfo()
{
 //   cout << "所有的用户信息: " << endl;
//    for(auto n : _netizens){
//        n->printInfo();
//    }
    for (auto g:_groupChatrooms){
        std::cout<<g->id()<<std::endl;
    }
    cout << endl;
}
