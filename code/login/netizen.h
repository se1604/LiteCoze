#ifndef NETIZEN_H
#define NETIZEN_H

#include <iostream>
#include <vector>
#include "privatechatroom.h"
#include "groupchatroom.h"
#include <string>

class GroupChatRoom;
class Conversion;

class Netizen
{
public:
    Netizen(long id, std::string password);
    Netizen(long id, std::string nickname, std::string avatar);
    Netizen(long id);
    Netizen(long id, std::string nickname, int i);
    Netizen();

    void selectFriend(long friendID);
    Conversion* createNewMessage(std::string content);
    bool parseJson(Conversion *conversion);
    Conversion* toJson();//将Netizen对象转换为json字符串
    Conversion* toJson(long roomID);
    void addFriend(Netizen *f, long roomID);
    void addGroup(GroupChatRoom *group);    //添加群和当前用户关联
    void setConversionType(int type);//设置Conversion的type

    void printInfo();      //显示好友列表
    void printGroupInfo();    //显示群列表
    bool isLoginSuccess();

    PrivateChatRoom *room(long roomID);
    long friendID(long roomID);

    long id() const;

    std::string groupName(long id);

private:
    long m_id;
    std::string m_password;
    std::string m_nickname;
    std::string m_avatar;
    std::vector<Netizen*> _friends;
    std::vector<PrivateChatRoom *> _privateChatRooms;
    std::vector<GroupChatRoom *> _groupChatRoom;
    Conversion* _conversion;
    PrivateChatRoom* m_selectedRoom;
};

#endif // NETIZEN_H
