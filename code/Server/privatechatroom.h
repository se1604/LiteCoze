#ifndef PRIVATECHATROOM_H
#define PRIVATECHATROOM_H
#include <vector>
#include <deque>

class Netizen;
class Message;

class PrivateChatRoom
{
public:
    friend class Netizen;
    PrivateChatRoom(long id, Netizen *netizen1, Netizen *netizen2);
    void addMessage(Message *msg);
    void sendOfflineMessages(Netizen *netizen);

    long id() const;


    void printInfo();//测试代码

private:
    long m_id;
    Netizen *_netizen1;
    Netizen *_netizen2;
    std::vector<Message*> _messages;
    std::deque<Message*> _offlineMessages;
};

#endif // PRIVATECHATROOM_H
