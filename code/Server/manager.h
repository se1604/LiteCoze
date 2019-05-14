#ifndef MANAGER_H
#define MANAGER_H

#include <boost/asio.hpp>
#include <vector>

class Netizen;
class PrivateChatRoom;
class Network;

class Manager
{
public:
    friend class Server;
    static Manager* getInstance();
    void addNetizen(Netizen *n);
    void addPrivateChatRoom(PrivateChatRoom *pcr);

    void setNetizenSocket(Network *network, Netizen *netizen);

    void printInfo();//测试代码
private:
    Manager();

    std::vector<Netizen*> _netizens;//系统的所有Netizen
    std::vector<PrivateChatRoom*> _privateChatRooms;//系统的所有PrivateChatRoom
    static Manager* _instance;
};

#endif // MANAGER_H
