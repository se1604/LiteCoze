#ifndef NETWORKTRANSMISSION_H
#define NETWORKTRANSMISSION_H
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Netizen;
class Conversion;
class Message;

class NetworkTransmission
{
public:
    NetworkTransmission(boost::asio::ip::tcp::socket socket);
    void sendAccountInfo();//检查登录的账户信息正确后发送完整的账户信息（包括好友关系）给客户端
    void do_accept_head();
    void do_accept_body();//一条消息分为3段，前4个字节是消息的头部（表示消息后两段的长度），第二段有2个字节（表示消息的类型，具体类型见说明文档），第三段是的消息内容
    void addNewMessageToRoom(Message *message);
    void send(Conversion *conversion);
    bool parseObject();//解析接受到的Json字节流

private:
    void do_send(Conversion *conversion);

    boost::asio::ip::tcp::socket m_socket;
    Netizen *_netizen;
    Conversion *_recentlyAcceptItem;//表示最近接受到的一条信息
};

#endif // NETWORKTRANSMISSION_H
