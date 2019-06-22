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
    GroupChatroom(long id=0, std::string nickname="", std::string avatar = "");
    void addMessage(Message* message);//添加一条聊天消息到房间
    void addGroupMember(Netizen *netizen);
    void addGroupOwner(Netizen *netizen);
    long id() const;

    bool parseJson(Conversion *conversion);
    Conversion* toJson(int type);
    Conversion* allToJson();
    void dealAddGroupChatroomRequest(Netizen *netizen);
    void sendAllOffLineAddGroupChatroomRequest();
    void initMemeber(Netizen *netizen);
    void addgroupTODB();

    void printMemeber();//测试

private:
    long m_id;
    std::string m_nickname;
    std::string m_avatar;//头像
    Netizen * _owner;//群主
    std::vector<Netizen*> _netizens;//群成员，包括群主
    std::deque<Netizen*> _allOffLineRequesters;//请求加入群的网民
    std::vector<Message*> _messages;
};

#endif // GROUPCHATROOM_H
