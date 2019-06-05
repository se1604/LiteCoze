#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>
#include "conversion.h"
#include <QString>

using boost::asio::ip::tcp;

class LogInUI;
class ClientUI;
class Client
{
public:
    static Client* getInstance();
    static Client* getInstance(boost::asio::io_context& io_context,const tcp::resolver::results_type &endpoints);
    void createNetizen();
    void connectServer(const tcp::resolver::results_type& endpoints);
    void logIn(long id, std::string password);
    void sendNewMessage(std::string content);
    void do_accept_head();
    void do_accept_body();
    void showAccountInfo(QString nickName, long id);
    void showFriendMsg(QString id, QString msg);
    void showAllOffLineMessages(Conversion *conversio);
    void selectFriend(long friendID);
    void send(Conversion *conversion);
    bool parseObject();
    bool isLoginSuccess();
    void startClientUI();
    LogInUI *getLogInUI() const;
    void setLogInUI(LogInUI *logInUI);

    ClientUI *getClientUI() const;
    void setClientUI(ClientUI *clientUI);

private:
    Client(boost::asio::io_context& io_context,const tcp::resolver::results_type &endpoints);
    void do_send(Conversion *conversion);

   boost::asio::io_context& m_io_context;
   tcp::socket m_socket;
   Conversion* _recentlyAcceptItem;

   static Client * _instance;

   LogInUI * _logInUI;
   ClientUI* _clientUI;
};

#endif // CLIENT_H
