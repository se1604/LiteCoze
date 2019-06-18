#ifndef PRIVATECHATROOM_H
#define PRIVATECHATROOM_H

#include <vector>
#include <deque>

class Netizen;
class Message;
class PrivateChatRoom
{
public:
    PrivateChatRoom(long id, Netizen *netizen1, Netizen *netizen2);
    void addMessage(Message* message);
    void sendMessage();
    void sendAllOffLineMessages(Netizen *netizen);
    Netizen* getFriend(Netizen *netizen);

    long id() const;

private:
    long m_id;
    Netizen *_netizen1;
    Netizen *_netizen2;
    std::vector<Message*> _messages;
    std::deque<Message*> _netizen1OfflineMessages;
    std::deque<Message*> _netizen2OfflineMessages;
};

#endif // PRIVATECHATROOM_H
