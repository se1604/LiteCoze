#ifndef GROUPCHATROOM_H
#define GROUPCHATROOM_H
#include <vector>
#include <deque>
#include <string>

class Netizen;
class Message;
class Conversion;

class GroupChatroom
{
public:
    GroupChatroom(long id, std::string nickname, std::string avatar = "");
    GroupChatroom();
    void addMessage(Message* message);//添加一条聊天消息到房间
    void addGroupMember(Netizen *netizen);
    long id() const;

    bool parseJson(Conversion *conversion);
    Conversion* toJson(int type);
    Conversion* allToJson();
    void dealAddGroupChatroomRequest(Netizen *netizen);
    void sendAllOffLineAddGroupChatroomRequest();

private:
    long m_id;
    std::string m_nickname;
    std::string m_avatar;//头像
    std::vector<Netizen*> _netizens;//群成员，默认第一个成员为群主
    std::deque<Netizen*> _allOffLineRequesters;//请求加入群的网民
    std::vector<Message*> _messages;
};

#endif // GROUPCHATROOM_H
