#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H
#include <boost/asio.hpp>

class NetworkTransmission;

class PrivateChat
{
public:
    PrivateChat(boost::asio::io_context &io_context, const boost::asio::ip::tcp::endpoint &endpoint);
    void accept();
    void checkLoginAccount(boost::asio::ip::tcp::socket socket);
    //void sendAccountInfo(NetworkTransmission *network);
    void sendAllOffLineMessages();
    void transferItem(NetworkTransmission *network);

private:
    boost::asio::ip::tcp::acceptor m_acceptor;

};

#endif // PRIVATECHAT_H
