#ifndef NETIZEN_H
#define NETIZEN_H
#include <string>
#include <vector>

class PrivateChatRoom;
class NetworkTransmission;
class Message;
class Conversion;

class Netizen
{
public:
    Netizen(long id,std::string password, std::string nickname);
    Netizen();
    void sendAccountInfo();
    void sendAllOffLineMessages();
    void sendMessage(Conversion* conversion);
    void addNewMessageToRoom(Message *message);
    void addFriend(Netizen *f, long roomID);
    bool parseJson(Conversion *conversion);
    Conversion* toJson();//将Netizen对象转换为json字符串
    bool checkAccount(Netizen* netizen, NetworkTransmission* networkTransmission);
    bool isAlreadyFriend(Netizen *netizen);
    //测试代码
    void printInfo();
    long id() const;
    bool isOnLine();
    void offLine();

private:
    long m_id;
    std::string m_password;
    std::string m_nickname;
    std::string m_avatar;
    std::vector<Netizen*> _friends;
    std::vector<PrivateChatRoom *> _privateChatRooms;
    NetworkTransmission *_networkTransmission;
    Conversion *_conversion;
};

#endif // NETIZEN_H
