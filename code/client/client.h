#ifndef CLIENT_H
#define CLIENT_H
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Conversion;
class Message;
//单例类
class Client
{
public:
    static Client* getInstance();
    static Client* getInstance(boost::asio::io_context& io_context,const tcp::resolver::results_type &endpoints);

    void write(Conversion *conversion);
    void close();

    void do_read_header();
    void parseObject();

    //void writeNetizen(Conversion *conversion);
private:
    Client(boost::asio::io_context& io_context,const  tcp::resolver::results_type &endpoints);
    void do_connect(const tcp::resolver::results_type& endpoints);
    void do_read_body();
    void do_write(Conversion *conversion);

    boost::asio::io_context& m_io_context;
    tcp::socket m_socket;
    static Client * _instance;

    Conversion *_conversion;
};

#endif // CLIENT_H
