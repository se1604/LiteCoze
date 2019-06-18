#ifndef MANAGER_H
#define MANAGER_H
#include <vector>

class Netizen;
class NetworkTransmission;
class Manager
{
public:    
    static Manager* getInstance();
    Netizen* checkAccount(Netizen *netizen, NetworkTransmission* networkTransmission);
    Netizen* findNetizen(Netizen *netizen);
    void addNetizen(Netizen *netizen);

    long allocateRoomID();

    void printInfo();//测试代码
private:
    Manager();
    std::vector<Netizen*> _netizens;
    static Manager* _instance;
};

#endif // MANAGER_H
