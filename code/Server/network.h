#ifndef NETWORK_H
#define NETWORK_H
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Netizen;
class Message;
class Conversion;

class Network
{
public:
    friend class Netizen;
    friend class Manager;
    Network(tcp::socket socket, Netizen *netizen);
    void write(Conversion *conversion);
    void close();

    void parseObject();
    bool socketIsOpen();

private:
    void do_read_header();
    void do_read_body();
    void do_write(Conversion *conversion);

    boost::asio::ip::tcp::socket m_socket;
    Netizen *_netizen;
    Conversion *_conversion;
};

#endif // NETWORK_H
