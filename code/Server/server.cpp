#include "server.h"
#include <iostream>
#include "networktransmission.h"

using namespace std;
using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context &io_context, const boost::asio::ip::tcp::endpoint &endpoint):
    m_acceptor(io_context, endpoint)
{

}

void Server::accept()
{
    m_acceptor.async_accept(
                [this](boost::system::error_code ec, tcp::socket socket)
    {
        if (!ec)
        {
            std::cout << "连接成功"<<std::endl;
            //auto networkTransmission = new NetworkTransmission(std::move(socket));
            checkLoginAccount(std::move(socket));
        }
        accept();
    });

}

void Server::checkLoginAccount(tcp::socket socket)
{
    auto networkTransmission = new NetworkTransmission(std::move(socket));
    transferItem(networkTransmission);
    //sendAccountInfo(networkTransmission);
    //transferOnLineMessage(networkTransmission);
}

//void PrivateChat::sendAccountInfo(NetworkTransmission *network)
//{
//    network->sendAccountInfo();

//}

void Server::transferItem(NetworkTransmission *network)
{
    network->do_accept_head();

}


