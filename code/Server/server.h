#ifndef SERVER_H
#define SERVER_H
#include <boost/asio.hpp>

class NetworkTransmission;

class Server
{
public:
    Server(boost::asio::io_context &io_context, const boost::asio::ip::tcp::endpoint &endpoint);
    void accept();//打开服务器，开始监听
    void checkLoginAccount(boost::asio::ip::tcp::socket socket);//有一个客户端连接成功后就去检查它的登录帐号是否正确
    //void sendAccountInfo(NetworkTransmission *network);
    //void sendAllOffLineMessages();
    void transferItem(NetworkTransmission *network);//开始传输信息

private:
    boost::asio::ip::tcp::acceptor m_acceptor;

};

#endif // SERVER_H
