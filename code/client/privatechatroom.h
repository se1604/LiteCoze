#ifndef PRIVATECHATROOM_H
#define PRIVATECHATROOM_H
#include <vector>

class Netizen;
class Message;

class PrivateChatRoom
{
public:
    friend class Netizen;
    PrivateChatRoom(long id, Netizen *netizen1, Netizen *netizen2);
    long id() const;
    void addMessage(Message *mes);


private:
    long m_id;
    Netizen *_netizen1;
    Netizen *_netizen2;
    std::vector<Message*> m_messages;
};

#endif // PRIVATECHATROOM_H
