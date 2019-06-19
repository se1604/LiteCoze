#include "privatechat.h"
#include <iostream>
#include "networktransmission.h"

using namespace std;
using boost::asio::ip::tcp;

PrivateChat::PrivateChat(boost::asio::io_context &io_context, const boost::asio::ip::tcp::endpoint &endpoint):
    m_acceptor(io_context, endpoint)
{

}

void PrivateChat::accept()
{
    m_acceptor.async_accept(
                [this](boost::system::error_code ec, tcp::socket socket)
    {
        if (!ec)
        {
            std::cout << "连接成功"<<std::endl;
            checkLoginAccount(std::move(socket));
        }
        accept();
    });

}

void PrivateChat::checkLoginAccount(tcp::socket socket)
{
    auto networkTransmission = new NetworkTransmission(std::move(socket));
    transferItem(networkTransmission);
}

void PrivateChat::transferItem(NetworkTransmission *network)
{
    network->do_accept_head();
}


