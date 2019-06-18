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
    ~Netizen();
    void sendAccountInfo();
    void sendAllOffLineMessages();
    void sendAllOffLineFriendRequest();
    void sendMessage(Conversion* conversion);
    void addNewMessageToRoom(Message *message);
    void addFriendRequest(Netizen *netizen);
    void addFriend(Netizen *f, long roomID);
    void acceptAddFriendRequest(Netizen *f);
    bool parseJson(Conversion *conversion);
    Conversion* toJson();//将Netizen对象转换为json字符串
    Conversion* toJson(long roomID);
    bool checkAccount(Netizen* netizen, NetworkTransmission* networkTransmission);
    bool findNetizen(Netizen* netizen);
    //测试代码
    void printInfo();
    long id() const;
    bool isOnLine();
    void offLine();

    void setConversionType(int type);

private:
    long m_id;
    std::string m_password;
    std::string m_nickname;
    std::string m_avatar;
    std::vector<Netizen*> _friends;
    std::vector<Netizen*> _friendRequests;
    std::vector<PrivateChatRoom *> _privateChatRooms;
    NetworkTransmission *_networkTransmission;
    Conversion *_conversion;
};

#endif // NETIZEN_H
