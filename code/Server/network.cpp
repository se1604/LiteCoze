#include "network.h"
#include "message.h"
#include "netizen.h"
#include "manager.h"
#include "privatechatroom.h"

#include <iostream>
#include <conversion.h>
using namespace  std;

extern boost::asio::io_context io_context;

Network::Network(tcp::socket socket, Netizen *netizen): m_socket(std::move(socket)), _netizen{netizen}
{
    _conversion = nullptr;
}

void Network::write(Conversion *conversion)
{
    boost::asio::post(io_context,
                      [this, conversion]()
    {
        do_write(conversion);
    });
}

void Network::close()
{
    boost::asio::post(io_context, [this]() {
        m_socket.close();
    });
}

void Network::parseObject()
{
    if (_conversion->getType() == 1){
        auto msg = new Message();
        msg->parseJson(_netizen, _conversion);
    }
    if (_conversion->getType() == 2)
    {
        _netizen->parseJson(_conversion);
        //auto netizen = new Netizen();
        //netizen->parseJson(_conversion);
        Manager::getInstance()->setNetizenSocket(this, _netizen);
        //cout << _netizen->_privateChatRooms.size() <<endl;

        _netizen->toJson(_netizen);

        write(_netizen->_conversion);

        _netizen->sendAllFriends();

        for (auto r : _netizen->_privateChatRooms){
            r->sendOfflineMessages(_netizen);
        }
    }
}

bool Network::socketIsOpen()
{
    if (m_socket.is_open()){
        return true;
    }
    return false;
}

void Network::do_read_header()
{
    _conversion = new Conversion();
    boost::asio::async_read(m_socket,
                            boost::asio::buffer(_conversion->data(), Conversion::header_length),
                            [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        cout << "error: "  << ec << endl;
        if (!ec && _conversion->decode_header())
        {
            do_read_body();
        }
        else
        {
            m_socket.close();
        }
    });
}

void Network::do_read_body()
{
    boost::asio::async_read(m_socket,
                            boost::asio::buffer(_conversion->type(), _conversion->body_length() + Conversion::type_length) ,
                            [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec && _conversion->decode_type())
        {
            //_recentReceiveMessage->parseJson(_netizen);
            //_recentReceiveMessage->receive();
            parseObject();
            //std::cout.write(_conversion->body(), _conversion->body_length());
            std::cout << "\n";

            //write(_conversion);

            //delete  _conversion;
            //_conversion = nullptr;
            //write

            do_read_header();
        }
        else
        {
            m_socket.close();
        }
    });
}

void Network::do_write(Conversion *conversion)
{
    boost::asio::async_write(m_socket,
                             boost::asio::buffer(conversion->data(), conversion->length()), [this, conversion](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            cout << "发送成功" << endl;
            //cout << conversion->data() << endl;
        }
        else
        {
            m_socket.close();
        }
    });
}
