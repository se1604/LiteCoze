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
    void addMessage(Message* message);//添加一条聊天消息到房间
    //void sendMessage();
    void sendAllOffLineMessages(Netizen *netizen);//发送所有的离线消息给网民
    Netizen* getFriend(Netizen *netizen);//得到一个房间中某个netizen的朋友

    long id() const;

private:
    long m_id;
    Netizen *_netizen1;
    Netizen *_netizen2;
    std::vector<Message*> _messages;
    std::deque<Message*> _netizen1OfflineMessages;
    std::deque<Message*> _netizen2OfflineMessages;
    //一个房间里有两个网民和分别存储网民1和网民2离线消息的容器，及这个房间中所有消息的容器
};

#endif // PRIVATECHATROOM_H
