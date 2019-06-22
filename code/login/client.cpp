#include "client.h"
#include <iostream>
#include "netizen.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "loginUI.h"
#include <QString>
#include "clientui.h"
#include "conversion.h"
#include "json/json.h"
#include "searchui.h"
#include "groupchatroom.h"

/////////////
using namespace std;

Client *Client::_instance = nullptr;

extern Netizen * netizen;

Client::Client(boost::asio::io_context &io_context,const tcp::resolver::results_type &endpoints):
    m_io_context{io_context}, m_socket{io_context}
{
    _recentlyAcceptItem = nullptr;
    connectServer(endpoints);
    _conversion = new Conversion();
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

void Client::connectServer(const tcp::resolver::results_type &endpoints)
{
    boost::asio::async_connect(m_socket, endpoints,
                               [this](boost::system::error_code ec, tcp::endpoint)
    {
        if (!ec)
        {
            std::cout << "连接成功" << std::endl;
            do_accept_head();
        }
        else{
            cout << "连接失败" << endl;
        }
    });
}

void Client::logIn(long id, string password)
{

    netizen = new Netizen(id, password);
    send(netizen->toJson());
}

void Client::findNetizen(long id)
{
    auto f = new Netizen(id);
    send(f->toJson());
}

void Client::findGroup(long id)
{
    auto group = new GroupChatRoom(id);
    send(group->toJson(11));
//    auto f = new Netizen(id);
//    f->setConversionType(11);
//    send(f->toJson());
}

void Client::addFriend(long id)
{
    auto f = new Netizen(id);
    f->setConversionType(7);
    send(f->toJson());
}

void Client::addGroup(long id, long roomid)
{
    auto group = new GroupChatRoom(roomid);
    send(group->toJson(13));
//    auto n = new Netizen(id);
//    n->setConversionType(13);
//    send(n->toJson(roomid));
}

void Client::acceptAddFriendRequest(Netizen *f)
{
    f->setConversionType(8);
    send(f->toJson());
}

void Client::acceptAddGroupRequest(long id, long roomid)
{
    auto n = new Netizen(id);
    n->setConversionType(14);
    send(n->toJson(roomid));
}

void Client::Register(long id, string nickname, string password)
{
    Json::Value root;
    std::ostringstream os;

    root["id"] = id;
    root["password"] = password;
    root["nickname"] = nickname;

    Json::StreamWriterBuilder writerBuilder;
    unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
    jsonWriter->write(root, &os);

    std::string jsonStr;
    jsonStr = os.str();

    char* c;
    const int len = jsonStr.length();
    c =new char[len+1];
    strcpy(c,jsonStr.c_str());

    _conversion->setType(5);
    _conversion->body_length(jsonStr.length());
    strcpy(_conversion->body(),c);

    _conversion->encode_header();
    _conversion->encode_type();

    send(_conversion);
}

void Client::sendNewMessage(string content)
{
    send(netizen->createNewMessage(content));
}

void Client::do_accept_head()
{
    _recentlyAcceptItem = new Conversion();
    boost::asio::async_read(m_socket,
                            boost::asio::buffer(_recentlyAcceptItem->data(), Conversion::header_length),
                            [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        cout << "ec: "  << ec << endl;
        if (!ec && _recentlyAcceptItem->decode_header())
        {
            do_accept_body();
        }
        else
        {
            cout << "读取head失败" << endl;
            m_socket.close();
        }
    });
}

void Client::do_accept_body()
{
    boost::asio::async_read(m_socket,
                            boost::asio::buffer(_recentlyAcceptItem->type(), _recentlyAcceptItem->body_length() + Conversion::type_length) ,
                            [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec && _recentlyAcceptItem->decode_type())
        {
            std::cout << "接收成功" << endl;
            //std::cout.write(_conversion->body(), _conversion->body_length());
            parseObject();

            std::cout << "\n";
            delete _recentlyAcceptItem;
            _recentlyAcceptItem = nullptr;

            do_accept_head();
        }
        else
        {
            cout << "读取body失败" << endl;
            m_socket.close();
        }
    });
}

void Client::showAccountInfo(QString nickName, long id, long roomid)
{
    emit _clientUI->showAccountInfo(nickName, QString::number(id, 10), QString::number(roomid, 10));
}

void Client::flushAccountInfo()
{
    netizen->printInfo();
}

void Client::clearAccountInfo()
{
    emit _clientUI->clearAccountInfo();
}

void Client::showFindInfo(QString nickName, long id)
{
    emit _searchUI->showFindInfo(nickName, QString::number(id, 10));
}

void Client::showNewFriendInfo(QString nickName, long id)
{
    emit _clientUI->showNewFriendInfo(nickName, QString::number(id, 10));
}

void Client::showFriendMsg(QString id, QString msg, QString roomid)
{
    emit _clientUI->showFriendMsg(id, msg, roomid);
}

void Client::selectFriend(long friendID)
{
    netizen->selectFriend(friendID);
}

bool Client::parseObject()
{
    if (_recentlyAcceptItem->getType() == 2){
        netizen->parseJson(_recentlyAcceptItem);
        return true;
    }
    if (_recentlyAcceptItem->getType() == 3){
        auto msg = new Message();
        msg->parseJson(_recentlyAcceptItem);
        return true;
    }
    if (_recentlyAcceptItem->getType() == 6){
        auto f = new Netizen();
        f->parseJson(_recentlyAcceptItem);
        return true;
    }
    if (_recentlyAcceptItem->getType() == 7){
        auto f = new Netizen();
        f->parseJson(_recentlyAcceptItem);
//        acceptAddFriendRequest(f);
        return true;
    }
    if (_recentlyAcceptItem->getType() == 8){
        auto f = new Netizen();
        netizen->parseJson(_recentlyAcceptItem);
        //netizen->addFriend(f)
        return true;
    }
    if (_recentlyAcceptItem->getType() == 10){
        auto gcr = new GroupChatRoom();
        gcr->parseJson(_recentlyAcceptItem);
        netizen->addGroup(gcr);
        return true;
    }
    if(_recentlyAcceptItem->getType() == 12){
        auto group = new GroupChatRoom();
        group->parseJson(_recentlyAcceptItem);
        return true;
    }
    if (_recentlyAcceptItem->getType() == 13){
        auto f = new Netizen();
        f->parseJson(_recentlyAcceptItem);
        return true;
    }
    return false;
}

bool Client::isLoginSuccess()
{
    if(netizen->isLoginSuccess()){
        return true;
    }
    return false;
}

void Client::startClientUI()
{
    emit _clientUI->showClientUI();
}

void Client::startSearchUI()
{
    emit _searchUI->showSearchUI();
}
void Client::send(Conversion *conversion)
{
    boost::asio::post(m_io_context,
                      [this, conversion]()
    {
        do_send(conversion);
    });
}
void Client::do_send(Conversion *conversion)
{
    boost::asio::async_write(m_socket,
                             boost::asio::buffer(conversion->data(), conversion->length()),[this, conversion](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            cout << conversion->data()<< endl;
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

SearchUi *Client::getSearchUI() const
{
    return _searchUI;
}

void Client::setSearchUI(SearchUi *searchUI)
{
    _searchUI = searchUI;
}

ClientUI *Client::getClientUI() const
{
    return _clientUI;
}

void Client::setClientUI(ClientUI *clientUI)
{
    _clientUI = clientUI;
}

LogInUI *Client::getLogInUI() const
{
    return _logInUI;
}

void Client::setLogInUI(LogInUI *logInUI)
{
    _logInUI = logInUI;
}
