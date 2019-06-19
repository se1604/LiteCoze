#include "manager.h"
#include "netizen.h"
#include <iostream>
#include <fstream>


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

long Manager::allocateRoomID()
{
    long number;
    ifstream ifs("../allocate");
    if (ifs.fail())
    {
        cout<<"打开文件错误!"<<endl;
        exit(0);
    }
    cout<<"打开文件成功!"<<endl;
    ifs >> number;
    cout<<number<<endl;
    ifs.close();

    ofstream ofs("../allocate");
    if (ofs.fail())
    {
        cout<<"打开文件错误!"<<endl;
        exit(0);
    }
    cout<<"打开文件成功!"<<endl;

    number++;
    ofs<<number;
    ofs.close();
    return number;
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

Netizen* Manager::findNetizen(Netizen *netizen)
{
    for(auto n : _netizens){
        if(n->findNetizen(netizen)){
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
