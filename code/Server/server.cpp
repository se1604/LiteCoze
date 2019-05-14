#include "server.h"
#include "manager.h"
#include "netizen.h"
#include "network.h"

#include <iostream>
using boost::asio::ip::tcp;

Server * Server::_instance = nullptr;

Server::Server(boost::asio::io_context &io_context, const boost::asio::ip::tcp::endpoint &endpoint):
    m_acceptor(io_context, endpoint)
{
}

Server *Server::getInstance(boost::asio::io_context &io_context, const tcp::endpoint &endpoint)
{
    if(_instance != nullptr)
        throw std::domain_error("Server已被实例化");
    _instance = new Server(io_context, endpoint);
    return _instance;
}

Server *Server::getInstance()
{
    if(_instance != nullptr)
        return _instance;
    throw std::domain_error("Server未实例化");
}

void Server::do_accept()
{
    m_acceptor.async_accept(
                [this](boost::system::error_code ec, tcp::socket socket)
    {
        if (!ec)
        {
            std::cout << "连接成功"<<std::endl;
            //将socket传给对应的Netizen
            //Manager::getInstance()->_netizens[0]->setNetwork(std::move(socket));
            auto n = new Netizen();
            n->setNetwork(std::move(socket));
            //n->setSocket(std::move(socket));
        }
        do_accept();
    });
}
