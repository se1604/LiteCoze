#ifndef MANAGER_H
#define MANAGER_H
#include <vector>
#include "dbbroker.h"

class Netizen;
class NetworkTransmission;
class Manager
{
public:    
    static Manager* getInstance();
    Netizen* checkAccount(Netizen *netizen, NetworkTransmission* networkTransmission);
    void addNetizen(Netizen *netizen);
    void initFriend();
    Netizen *getNetizen(long id);

    void printInfo();//测试代码
private:
    Manager();
    std::vector<Netizen*> _netizens;
    static Manager* _instance;
};

#endif // MANAGER_H
