#include "privatechatroom.h"

PrivateChatRoom::PrivateChatRoom(long id, Netizen *netizen1, Netizen *netizen2):m_id{id}, _netizen1{netizen1}, _netizen2{netizen2}
{

}

Conversion* PrivateChatRoom::createNewMessage(std::string content)
{
    auto msg = new Message(content, this);
    addMessage(msg);
    return msg->toJson();
}
//PrivateChatRoom* PrivateChatRoom::room(Netizen *f)
//{
//    if((_netizen1 == f) || (_netizen2 == f)){
//        return this;
//    }
//    return nullptr;
//}

long PrivateChatRoom::id() const
{
    return m_id;
}
void PrivateChatRoom::addMessage(Message *mes){
    _messages.push_back(mes);
}
