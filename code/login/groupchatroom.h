#ifndef GROUPCHATROOM_H
#define GROUPCHATROOM_H
#include <string>
#include <vector>
#include "message.h"
class Netizen;

class GroupChatRoom
{
public:
    GroupChatRoom(long id, std::string name, std::string touxiang, std::vector<Netizen*> netizens);
    void addNetizen(Netizen * netizen);

    Conversion* createNewMessage(std::string content);
    void addMessage(Message *mes);
    long id() const;
    std::string name() const;
    void setName(const std::string &name);

    std::string touxiang() const;
    void setTouxiang(const std::string &touxiang);

private:
    long m_id;
    std::string m_name;
    std::string m_touxiang;
    std::vector<Netizen*> _netizens;
    std::vector<Message*> _messages;
};

#endif // GROUPCHATROOM_H
