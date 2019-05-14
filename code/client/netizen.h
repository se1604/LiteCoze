#ifndef NETIZEN_H
#define NETIZEN_H
#include <string>
#include <vector>

class PrivateChatRoom;
class Conversion;

class Netizen
{
public:
    friend class Client;
    Netizen(long id = 0, std::string nickname = "");
    void addFriend(Netizen *f, long roomID);

    void printInfo();//测试代码

    std::vector<PrivateChatRoom *> privateChatRooms() const;
    PrivateChatRoom *getPrivateChatRoom(long roomID);
    PrivateChatRoom *getPrivateChatRoomN(long nitizenID);
    long id() const;

    std::string toJson();//将Netizen对象转换为json字符串
    long parseJson(Conversion *conversion);//解析json字符串

    void write();

    void setId(long id);

private:
    long m_id;
    std::string m_nickname;
    std::vector<Netizen*> _friends;
    std::vector<PrivateChatRoom *> _privateChatRooms;
    Conversion * _conversion;
};

#endif // NETIZEN_H
