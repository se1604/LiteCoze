#include "privatechatroom.h"

PrivateChatRoom::PrivateChatRoom(long id, Netizen *netizen1, Netizen *netizen2):
    m_id{id}, _netizen1{netizen1}, _netizen2{netizen2} {}

long PrivateChatRoom::id() const
{
    return m_id;
}
void PrivateChatRoom::addMessage(Message *mes)
{
    m_messages.push_back(mes);
}
