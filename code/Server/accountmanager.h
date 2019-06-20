#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H
#include <vector>
#include "dbbroker.h"

class Netizen;
class NetworkTransmission;
class AccountManager
{
public:    
    static AccountManager* getInstance();
    Netizen* checkAccount(Netizen *netizen, NetworkTransmission* networkTransmission);//检查登录账户信息
    Netizen* findNetizen(Netizen *netizen);//查找网民
    void addNetizen(Netizen *netizen);
    void initFriend();
    void initGroup();
    Netizen *getNetizen(long id);//通过网民id号找到网民

    void printInfo();//测试代码
private:
    AccountManager();
    std::vector<Netizen*> _netizens;
    static AccountManager* _instance;
};

#endif // ACCOUNTMANAGER_H
