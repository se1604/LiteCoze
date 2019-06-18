#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>
#include "conversion.h"

using boost::asio::ip::tcp;

class Netizen;

class Client
{
public:
    static Client* getInstance();
    static Client* getInstance(boost::asio::io_context& io_context,const tcp::resolver::results_type &endpoints);
    void createNetizen();
    void connectServer(const tcp::resolver::results_type& endpoints);
    void logIn(long id, std::string password);
//----------------------------------------------
    void findNetizen(long id);//查找
    void addFriend(long id);//请求添加好友
    void acceptAddFriendRequest(Netizen *f);//接受请求
//----------------------------------------------
    void sendNewMessage(std::string content);
    void do_accept_head();
    void do_accept_body();
    void showAccountInfo(Conversion *conversio);
    void showAllOffLineMessages(Conversion *conversio);
    void selectFriend(long friendID);
    void send(Conversion *conversion);

    //----------------------------------------------
    bool parseObject();
    //----------------------------------------------

    bool isLoginSuccess();

private:
    Client(boost::asio::io_context& io_context,const tcp::resolver::results_type &endpoints);
    void do_send(Conversion *conversion);

   boost::asio::io_context& m_io_context;
   tcp::socket m_socket;
   Conversion* _recentlyAcceptItem;

   static Client * _instance;
};

#endif // CLIENT_H
