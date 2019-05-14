#include "client.h"
#include <iostream>
#include "message.h"
#include "netizen.h"
#include "conversion.h"
#include "netizen.h"

using namespace std;
extern Netizen *netizen;

Client *Client::_instance = nullptr;


Client::Client(boost::asio::io_context &io_context,const tcp::resolver::results_type &endpoints):
    m_io_context{io_context}, m_socket{io_context}
{
    _conversion = nullptr;
    do_connect(endpoints);
}
Client *Client::getInstance()
{
    if(_instance != nullptr)
        return _instance;
    throw domain_error("Client未实例化");
}

Client *Client::getInstance(boost::asio::io_context &io_context,const tcp::resolver::results_type &endpoints)
{
    if(_instance != nullptr)
      throw domain_error("Client已被实例化");
    _instance = new Client(io_context, endpoints);
    return _instance;
}

void Client::write(Conversion *conversion)
{
    boost::asio::post(m_io_context,
                      [this, conversion]()
    {
        do_write(conversion);
    });
}

void Client::close()
{
    cout << "关闭套接字" << endl;
    boost::asio::post(m_io_context, [this]() { m_socket.close(); });
}

void Client::parseObject()
{
    if (_conversion->getType() == 1){
        auto msg = new Message();
        msg->parseJson(_conversion);
    }
    if (_conversion->getType() == 2)
    {
        if (netizen->m_nickname == ""){
            netizen->parseJson(_conversion);
        }
        else if (netizen->m_nickname != "") {
            auto n = new Netizen();
            netizen->addFriend(n, n->parseJson(_conversion));
        }
    }
}


void Client::do_connect(const tcp::resolver::results_type &endpoints)
{
    boost::asio::async_connect(m_socket, endpoints,
                               [this](boost::system::error_code ec, tcp::endpoint)
    {
        if (!ec)
        {
            std::cout << "连接成功" << std::endl;
            do_read_header();
        }
        else{
            cout << "连接失败" << endl;
        }
    });
}

void Client::do_read_header()
{
    _conversion = new Conversion();
    boost::asio::async_read(m_socket,
                            boost::asio::buffer(_conversion->data(), Conversion::header_length),
                            [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec && _conversion->decode_header())
        {
            do_read_body();
        }
        else
        {
            cout << "读取header失败" << endl;
            m_socket.close();
        }
    });
}

void Client::do_read_body()
{
    boost::asio::async_read(m_socket,
                            boost::asio::buffer(_conversion->type(), _conversion->body_length() + Conversion::type_length) ,
                            [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec && _conversion->decode_type())
        {
            std::cout << "接收成功" << endl;
            //std::cout.write(_conversion->body(), _conversion->body_length());
            parseObject();

            std::cout << "\n";
            delete _conversion;
            _conversion = nullptr;

            do_read_header();
        }
        else
        {
            cout << "读取body失败" << endl;
            m_socket.close();
        }
    });
}

void Client::do_write(Conversion *conversion)
{
    boost::asio::async_write(m_socket,
                             boost::asio::buffer(conversion->data(), conversion->length()),[this, conversion](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            cout << "发送成功" <<endl;
            //cout << conversion->data() << conversion->length() << endl;
        }
        else
        {
            cout << "发送失败" << endl;
            m_socket.close();
        }
    });
}
