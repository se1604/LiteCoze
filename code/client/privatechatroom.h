#ifndef PRIVATECHATROOM_H
#define PRIVATECHATROOM_H
#include <string>
#include <vector>
#include "message.h"
class Netizen;

class PrivateChatRoom
{
public:
    PrivateChatRoom(long id, Netizen *netizen1, Netizen *netizen2);

    Conversion* createNewMessage(std::string content);
    void addMessage(Message *mes);
//    PrivateChatRoom* room(Netizen *f);
    long id() const;

private:
    long m_id;
    Netizen *_netizen1;
    Netizen *_netizen2;
    std::vector<Message*> _messages;
};

#endif // PRIVATECHATROOM_H
