#ifndef NETIZEN_H
#define NETIZEN_H
#include <string>
#include <vector>
#include <deque>

class PrivateChatRoom;
class GroupChatroom;
class NetworkTransmission;
class Message;
class Conversion;

class Netizen
{
public:
    Netizen(long id,std::string password, std::string nickname);
    Netizen();
    ~Netizen();
    void send(Conversion* conversion);
    void sendAccountGroupChatrooms();
    void sendAllOffLineMessages();
    void sendAllOffLineFriendRequest();//发送所有离线添加朋友的请求
    void sendAllOffLineAddGroupChatroomRequest();
    void sendMessage(Conversion* conversion);
    void addNewMessageToRoom(Message *message);
    void addNewOffLineMessage(Message *message);
    void dealAddFriendRequest(Netizen *netizen);//处理添加好友的请求
    void addFriend(Netizen *f, long roomID);//添加好友
    void acceptAddFriendRequest(Netizen *f);//接受添加好友的请求
    void acceptAddGroupChatroomRequest(Netizen *netizen, long roomID);//接受添加群的请求
    long parseJson(Conversion *conversion);
    Conversion* toJson();//将Netizen对象转换为json字符串
    Conversion* toJson(long roomID);
    bool checkAccount(Netizen* netizen, NetworkTransmission* networkTransmission);
    //bool findNetizen(Netizen* netizen);//查找网民
    bool isAlreadyFriend(Netizen *netizen);//检查两个网民之间是否已为朋友关系
    void addAccount();//添加账户信息到数据库
    //测试代码
    void printInfo();
    long id() const;
    bool isOnLine();//检查网民是否在线
    void offLine();//网民下线

    void setConversionType(int type);//设置信息的类型

    std::string nickname() const;

    std::string avatar() const;

private:
    long m_id;
    std::string m_password;
    std::string m_nickname;
    std::string m_avatar;//头像
    std::vector<Netizen*> _friends;
    std::deque<Netizen*> _friendRequests;//未发送的添加朋友的请求
    std::vector<PrivateChatRoom *> _privateChatRooms;//该网民的所有私聊房间
    std::vector<GroupChatroom*> _groupChatrooms;//该网民的所有群聊房间
    std::vector<GroupChatroom*> _ownGroupChatroom;//该网民管理的所有群聊房间
    NetworkTransmission *_networkTransmission;
    Conversion *_conversion;
    std::deque<Message *> _allOffLineMessages;//临时存储网民所有的离线消息
};

#endif // NETIZEN_H
