#include "groupchatroom.h"
#include "netizen.h"

GroupChatRoom::GroupChatRoom(long id, std::string name, std::string touxiang,  std::vector<Netizen*> netizens) : m_id{id}, m_name{name}, m_touxiang{touxiang}, _netizens(netizens)
{

}

void GroupChatRoom::addNetizen(Netizen *netizen)
{
    _netizens.push_back(netizen);
}

Conversion *GroupChatRoom::createNewMessage(std::string content)
{
    auto msg = new Message(content, id());
    addMessage(msg);
    return msg->toJson();
}

void GroupChatRoom::addMessage(Message *mes)
{
    _messages.push_back(mes);
}

long GroupChatRoom::id() const
{
    return m_id;
}

std::string GroupChatRoom::name() const
{
    return m_name;
}

void GroupChatRoom::setName(const std::string &name)
{
    m_name = name;
}

std::string GroupChatRoom::touxiang() const
{
    return m_touxiang;
}

void GroupChatRoom::setTouxiang(const std::string &touxiang)
{
    m_touxiang = touxiang;
}
