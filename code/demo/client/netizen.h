#ifndef NETIZEN_H
#define NETIZEN_H

#include <iostream>
#include <vector>
#include "privatechatroom.h"

class Conversion;

class Netizen
{
public:
    Netizen(long id, std::string password);
    Netizen(long id, std::string nickname, std::string avatar);

    void selectFriend(long friendID);
    Conversion* createNewMessage(std::string content);
    bool parseJson(Conversion *conversion);
    Conversion* toJson();//将Netizen对象转换为json字符串
    void addFriend(Netizen *f, long roomID);
    //测试代码
    void printInfo();
    bool isLoginSuccess();

    PrivateChatRoom *room(long roomID);

private:
    long m_id;
    std::string m_password;
    std::string m_nickname;
    std::string m_avatar;
    std::vector<Netizen*> _friends;
    std::vector<PrivateChatRoom *> _privateChatRooms;
    Conversion* _conversion;
    PrivateChatRoom* m_selectedRoom;
};

#endif // NETIZEN_H
