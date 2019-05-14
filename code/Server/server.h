#ifndef SERVER_H
#define SERVER_H
#include <boost/asio.hpp>

class Server
{
public:
    static Server *getInstance(boost::asio::io_context &io_context, const boost::asio::ip::tcp::endpoint &endpoint);
    static Server *getInstance();
    void do_accept();

private:
    Server(boost::asio::io_context &io_context, const boost::asio::ip::tcp::endpoint &endpoint);

    boost::asio::ip::tcp::acceptor m_acceptor;
    static Server *_instance;
};

#endif // SERVER_H
