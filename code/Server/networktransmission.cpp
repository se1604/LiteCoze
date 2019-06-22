#include "networktransmission.h"
#include "conversion.h"
#include "netizen.h"
#include "message.h"
#include "accountmanager.h"
#include "groupchatroom.h"

#include <iostream>

extern boost::asio::io_context io_context;
using namespace std;

NetworkTransmission::NetworkTransmission(tcp::socket socket): m_socket(std::move(socket))
{
    //do_accept_head();
}

void NetworkTransmission::sendAccountInfo()
{
    _netizen->setConversionType(2);
    send(_netizen->toJson());
}

void NetworkTransmission::do_accept_head()
{
    _recentlyAcceptItem = new Conversion();
    boost::asio::async_read(m_socket,
                            boost::asio::buffer(_recentlyAcceptItem->data(), Conversion::header_length),
                            [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        cout << "ec: "  << ec << endl;
        cout << _recentlyAcceptItem->data();
        if (!ec && _recentlyAcceptItem->decode_header())
        {
            do_accept_body();
        }
        else
        {
            m_socket.close();
            _netizen->offLine();
        }
    });
}

void NetworkTransmission::do_accept_body()
{
    boost::asio::async_read(m_socket,
                            boost::asio::buffer(_recentlyAcceptItem->type(), _recentlyAcceptItem->body_length() + Conversion::type_length) ,
                            [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec && _recentlyAcceptItem->decode_type())
        {

            cout << "接收成功" << endl;
            cout << _recentlyAcceptItem->data() << endl;
            //cout << _recentlyAcceptItem->data() << endl;
            parseObject();
            do_accept_head();
            std::cout << "\n";

        }
        else
        {
            m_socket.close();
            _netizen->offLine();
        }
    });
}

void NetworkTransmission::addNewMessageToRoom(Message *message)
{
    _netizen->addNewMessageToRoom(message);
}

void NetworkTransmission::send(Conversion *conversion)
{
    boost::asio::post(io_context,
                      [this, conversion]()
    {
        do_send(conversion);
    });
}

bool NetworkTransmission::parseObject()
{
    if(_recentlyAcceptItem->getType() == 1){
        auto netizen = new Netizen();
        netizen->parseJson(_recentlyAcceptItem);
        _netizen = AccountManager::getInstance()->checkAccount(netizen, this);
        if(_netizen){
            sendAccountInfo();
            _netizen->printInfo();
            _netizen->sendAccountGroupChatrooms();
            _netizen->sendAllOffLineMessages();
            _netizen->sendAllOffLineFriendRequest();
            _netizen->sendAllOffLineAddGroupChatroomRequest();
            return true;
        } else{
//            throw domain_error("检测失败");
            return false;
        }
    }else if(_recentlyAcceptItem->getType() == 3){
        auto msg = new Message();
        msg->parseJson(_recentlyAcceptItem, _netizen->id());
        addNewMessageToRoom(msg);
        return true;
    }else if(_recentlyAcceptItem->getType() == 4) {
        auto netizen = new Netizen();
        netizen->parseJson(_recentlyAcceptItem);
        auto f = AccountManager::getInstance()->findNetizen(netizen);
        delete netizen;
        netizen = nullptr;
        if(f){
            f->setConversionType(6);
            send(f->toJson());
            return true;
        } else{
//            throw domain_error("检测失败");
            return false;
        }
    }else if (_recentlyAcceptItem->getType() == 5) {
        //register
        auto netizen = new Netizen();
        netizen->parseJson(_recentlyAcceptItem);
        AccountManager::getInstance()->addNetizen(netizen);
        netizen->addAccount();
        //DBBroker::getInstance()->addAccountTODB(netizen);
    }else if(_recentlyAcceptItem->getType() == 7) {
        auto netizen = new Netizen();
        netizen->parseJson(_recentlyAcceptItem);
        auto f = AccountManager::getInstance()->findNetizen(netizen);
        delete netizen;
        netizen = nullptr;
        if(f){
            f->dealAddFriendRequest(_netizen);
            //send(f->toSimpleJson());
            return true;
        } else{
//            throw domain_error("检测失败");
            return false;
        }
    }else if(_recentlyAcceptItem->getType() == 8) {
        auto netizen = new Netizen();
        netizen->parseJson(_recentlyAcceptItem);
        auto f = AccountManager::getInstance()->findNetizen(netizen);
        delete netizen;
        netizen = nullptr;
        if(f){
            _netizen->acceptAddFriendRequest(f);
            //f->addFriendRequest(_netizen);
            //send(f->toSimpleJson());
            return true;
        } else{
//            throw domain_error("检测失败");
            return false;
        }
    }else if (_recentlyAcceptItem->getType() == 9) {
        auto gcr = new GroupChatroom();
        gcr->parseJson(_recentlyAcceptItem);
        AccountManager::getInstance()->addGroupChatroom(gcr);
        gcr->addGroupMember(_netizen);
        gcr->addGroupOwner(_netizen);
        send(gcr->toJson(10));
        gcr->addgroupTODB();
    }else if (_recentlyAcceptItem->getType() == 11) {
        auto gcr = new GroupChatroom();
        gcr->parseJson(_recentlyAcceptItem);
        cout << "开始查找" << endl;
        auto g = AccountManager::getInstance()->findGroupChatroom(gcr);
        delete gcr;
        gcr = nullptr;
        if(g){
            send(g->toJson(12));
        }
    }else if(_recentlyAcceptItem->getType() == 13) {
        auto gcr = new GroupChatroom();
        gcr->parseJson(_recentlyAcceptItem);
        auto g = AccountManager::getInstance()->findGroupChatroom(gcr);
        delete gcr;
        gcr = nullptr;
        if(g){
            g->dealAddGroupChatroomRequest(_netizen);
            return true;
        } else{
//            throw domain_error("检测失败");
            return false;
        }
    }else if(_recentlyAcceptItem->getType() == 14) {
        auto netizen = new Netizen();
        long roomID = netizen->parseJson(_recentlyAcceptItem);
        auto n = AccountManager::getInstance()->findNetizen(netizen);
        delete netizen;
        netizen = nullptr;
        if(n){
            _netizen->acceptAddGroupChatroomRequest(n, roomID);
            //f->addFriendRequest(_netizen);
            //send(f->toSimpleJson());
            return true;
        } else{
//            throw domain_error("检测失败");
            return false;
        }
    }
    return false;

}

void NetworkTransmission::do_send(Conversion *conversion)
{
    boost::asio::async_write(m_socket,
                             boost::asio::buffer(conversion->data(), conversion->length()), [this, conversion](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            cout << "发送成功" << endl;
            cout << conversion->data() << endl;
        }
        else
        {
            m_socket.close();
            _netizen->offLine();
        }
    });
}
