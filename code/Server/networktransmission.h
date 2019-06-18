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
    void sendAccountInfo();
    void do_accept_head();
    void do_accept_body();
    void addNewMessageToRoom(Message *message);
    void send(Conversion *conversion);
    bool parseObject();

private:
    void do_send(Conversion *conversion);

    boost::asio::ip::tcp::socket m_socket;
    Netizen *_netizen;
    Conversion *_recentlyAcceptItem;
};

#endif // NETWORKTRANSMISSION_H
