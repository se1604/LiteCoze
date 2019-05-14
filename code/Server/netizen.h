#ifndef NETIZEN_H
#define NETIZEN_H
#include <string>
#include <vector>
#include <boost/asio.hpp>

class PrivateChatRoom;
class Manager;
class Message;
class Network;
class Conversion;

class Netizen
{
public:
    friend class Manager;
    friend class PrivateChatRoom;
    friend class Network;
    Netizen(long id, std::string nickname);
    Netizen();
    void addFriend(Netizen *f, long roomID);
    PrivateChatRoom *getPrivateChatRoom(long id);
    long getPrivateChatRoomID(Netizen *f);
    void setNetwork(boost::asio::ip::tcp::socket socket);

    //void setSocket(boost::asio::ip::tcp::socket socket);
    void sendAllFriends();

    void printInfo();

    std::string toJson(Netizen *netizen);//将Netizen对象转换为json字符串
    bool parseJson(Conversion *conversion);//解析json字符串

private:
    long m_id;
    std::string m_nickname;
    std::vector<Netizen*> _friends;
    std::vector<PrivateChatRoom *> _privateChatRooms;
    Network *_network;
    Conversion *_conversion;
};

#endif // NETIZEN_H
