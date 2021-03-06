#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>
#include "conversion.h"
#include <QString>
#include "string"

using boost::asio::ip::tcp;

class LogInUI;
class ClientUI;
class Netizen;
class SearchUi;         //////////////////
class Client
{
public:
    static Client* getInstance();
    static Client* getInstance(boost::asio::io_context& io_context,const tcp::resolver::results_type &endpoints);
    void createNetizen();
    void connectServer(const tcp::resolver::results_type& endpoints);
    void logIn(long id, std::string password);
    void findNetizen(long id);//查找
    void findGroup(long id);     //查找群
    void addFriend(long id);//请求添加好友
    void addGroup(long id, long roomid);//请求添加好群
    void acceptAddFriendRequest(Netizen *f);//接受请求
    void acceptAddGroupRequest(long id, long roomid); //接受请求加入群
    void creatGroup(std::string name);        //创建群
    void Register(long id, std::string nickname, std::string password);   ////////////
    void sendNewMessage(std::string content);
    void do_accept_head();
    void do_accept_body();
    void showAccountInfo(QString nickName, long id, long roomid);
    void flushAccountInfo();
    void clearAccountInfo();
    void showFindInfo(QString nickName, long id);
    void showNewFriendInfo(QString nickName, long id);
    void showFriendMsg(QString id, QString msg, QString roomid);
    void showAllOffLineMessages(Conversion *conversio);
    void selectFriend(long friendID);
    void send(Conversion *conversion);
    void sendGroupNewMessage(long roomid, QString content);
    bool parseObject();
    bool isLoginSuccess();
    void startClientUI();
    void startSearchUI();                   ////////////////////
    LogInUI *getLogInUI() const;
    void setLogInUI(LogInUI *logInUI);

    ClientUI *getClientUI() const;
    void setClientUI(ClientUI *clientUI);


    SearchUi *getSearchUI() const;            /////////////////
    void setSearchUI(SearchUi *searchUI);        /////////////////
private:
    Client(boost::asio::io_context& io_context,const tcp::resolver::results_type &endpoints);
    void do_send(Conversion *conversion);

   boost::asio::io_context& m_io_context;
   tcp::socket m_socket;
   Conversion* _recentlyAcceptItem;
   Conversion* _conversion;

   static Client * _instance;

   LogInUI * _logInUI;
   ClientUI* _clientUI;
   SearchUi * _searchUI;                 /////////////////
};

#endif // CLIENT_H
