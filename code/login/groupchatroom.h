#ifndef GROUPCHATROOM_H
#define GROUPCHATROOM_H
#include <string>
#include <vector>
#include "message.h"
class Netizen;

class GroupChatRoom
{
public:
    GroupChatRoom(long id = 0, std::string name = "", std::string touxiang = "");
    void addNetizen(Netizen * netizen);

    Conversion* createNewMessage(std::string content);
    void addMessage(Message *mes);
    bool parseJson(Conversion *conversion);
    Conversion* toJson(int type);
    long id() const;
    std::string name() const;

    std::string touxiang() const;

private:
    long m_id;
    std::string m_nickname;
    std::string m_avatar;
    std::vector<Netizen*> _netizens;
    std::vector<Message*> _messages;
};

#endif // GROUPCHATROOM_H
