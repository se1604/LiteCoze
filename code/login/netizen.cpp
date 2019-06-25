#include "netizen.h"
#include "conversion.h"
#include <iostream>
#include <cstring>
#include <memory>
#include <sstream>
#include "privatechatroom.h"
#include "client.h"
#include <QString>
#include "privatechat.h"
#include "groupchat.h"

#include "json/json.h"
using namespace std;
extern Netizen * netizen;

Netizen::Netizen(long id, string password):
    m_id{id}, m_password{password}, m_nickname{""}, m_avatar{""}
{
    _conversion = new Conversion();
    _conversion->setType(1);
}

Netizen::Netizen(long id, string nickname, string avatar):
    m_id{id}, m_nickname{nickname}, m_avatar{avatar}
{
    m_password = string("");
}

Netizen::Netizen(long id):
    m_id{id}, m_password{""}, m_nickname{""}, m_avatar{""}
{
    _conversion = new Conversion();
    _conversion->setType(4);
}

Netizen::Netizen(long id, string nickname, int i):
    m_id{id}, m_password{""}, m_nickname{nickname}, m_avatar{""}
{
    _conversion = new Conversion();
}

Netizen::Netizen():
    m_id{0}, m_password{""}, m_nickname{""}, m_avatar{""}
{
    _conversion = new Conversion();
}

void Netizen::selectFriend(long friendID)
{
    for(auto f : _friends){
        if (f->m_id == friendID){
            m_selectedRoom = f->_privateChatRooms[0];
        }
    }
}

Conversion* Netizen::createNewMessage(string content)
{
    //m_selectedRoom = _privateChatRooms[0];
    return m_selectedRoom->createNewMessage(content);
}


bool Netizen::parseJson(Conversion *conversion)
{
    char* c = conversion->body();
    if (strlen(c) == 0)
        return false;


    JSONCPP_STRING errs;
    Json::Value root, friendID, friendNickname, roomID;


    Json::CharReaderBuilder readerBuilder;
    std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());

    bool res;
    res = jsonReader->parse(c, c+strlen(c), &root, &errs);


    if (!res || !errs.empty()) {
        std::cout << "parseJson err. " << errs << std::endl;
    }

    if(conversion->getType() == 2){
        friendID = root["friendID"];
        friendNickname = root["friendNickname"];
        roomID = root["roomID"];

        for(unsigned int i =0; i < friendID.size(); i++){
            auto f = new Netizen(friendID[i].asLargestInt(), friendNickname[i].asString(), "");
            addFriend(f, roomID[i].asLargestInt());
        }
        printInfo();
        printGroupInfo();
        return true;
    }
    if(conversion->getType() == 8){
        auto f = new Netizen(root["id"].asLargestInt(),
                root["nickname"].asString(), "");
        addFriend(f, root["roomID"].asLargestInt());
        printInfo();
        return true;
    }
    if(conversion->getType() == 6){
        m_id = root["id"].asLargestInt();
        m_nickname = root["nickname"].asString();
        Client::getInstance()->showFindInfo(QString::fromStdString(m_nickname), m_id);
        return true;
    }
    if(conversion->getType() == 7){
        m_id = root["id"].asLargestInt();
        m_nickname = root["nickname"].asString();
        std::cout << "id: " << m_id << std::endl;
        Client::getInstance()->showNewFriendInfo(QString::fromStdString(m_nickname), m_id);
        return true;
    }

    if(conversion->getType() == 13){
        m_id = root["id"].asLargestInt();
        m_nickname = root["nickname"].asString();
        long groupId = root["roomID"].asLargestInt();
        std::cout << "id: " << m_id << std::endl;
        GroupChat::getInstance()->showNewGroupInfo(QString::fromStdString(m_nickname), QString::number(m_id, 10), QString::fromStdString(netizen->groupName(groupId)), QString::number(groupId));
        //root["roomID"].asLargestInt()
        return true;
    }
    //测试
    std::cout << "id: " << m_id << ": ";
    std::cout << "password: " << m_password << std::endl;
    std::cout << "nickname: " << m_nickname << std::endl;
//    printInfo();


    return true;
}

Conversion* Netizen::toJson()
{
    Json::Value root, friendID, friendNickname, roomID;
    std::ostringstream os;

    root["id"] = m_id;
    root["password"] = m_password;
    root["nickname"] = m_nickname;


    Json::StreamWriterBuilder writerBuilder;
    unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
    jsonWriter->write(root, &os);

    std::string jsonStr;
    jsonStr = os.str();

    //std::cout << "Json:\n" << jsonStr << std::endl;

    char* c;
    const int len = jsonStr.length();
    c =new char[len+1];
    strcpy(c,jsonStr.c_str());

    _conversion->body_length(jsonStr.length());
    //_conversion->m_body_length = jsonStr.length();
    //memcpy(data_ + header_length, c, body_length_);
    strcpy(_conversion->body(),c);

    _conversion->encode_header();
    _conversion->encode_type();
    //cout << _conversion->data() << endl;
    return _conversion;
}

Conversion *Netizen::toJson(long roomID)
{
    Json::Value root;
    std::ostringstream os;

    root["id"] = m_id;
    root["roomID"] = roomID;


    Json::StreamWriterBuilder writerBuilder;
    unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
    jsonWriter->write(root, &os);

    std::string jsonStr;
    jsonStr = os.str();

    //std::cout << "Json:\n" << jsonStr << std::endl;

    char* c;
    const int len = jsonStr.length();
    c =new char[len+1];
    strcpy(c,jsonStr.c_str());

    _conversion->body_length(jsonStr.length());
    //_conversion->m_body_length = jsonStr.length();
    //memcpy(data_ + header_length, c, body_length_);
    strcpy(_conversion->body(),c);

    _conversion->encode_header();
    _conversion->encode_type();
    //cout << _conversion->data() << endl;
    return _conversion;
}

void Netizen::addFriend(Netizen *f, long roomID)
{
    _friends.push_back(f);
    f->_friends.push_back(this);
    PrivateChatRoom *room = new PrivateChatRoom(roomID, this, f);
    _privateChatRooms.push_back(room);
    f->_privateChatRooms.push_back(room);
    cout << m_nickname << "与" << f->m_nickname << "成为朋友" << endl << endl;
}

void Netizen::addGroup(GroupChatRoom *group)
{
    _groupChatRoom.push_back(group);
}


void Netizen::setConversionType(int type)
{
    _conversion->setType(type);
}

void Netizen::addInGroup(long roomid, long netizenid)
{
    for(auto f : _groupChatRoom){
        if(f->id() == roomid){
            Netizen * a = new Netizen(netizenid);
            f->addNetizen(a);
        }
    }
}

void Netizen::printInfo(){
    Client::getInstance()->clearAccountInfo();
    cout << "所有的好友信息： " << endl;
    for(auto f : _friends){
        Client::getInstance()->showAccountInfo(QString::fromStdString(f->m_nickname), f->m_id, f->_privateChatRooms[0]->id());
    }
}

void Netizen::printGroupInfo()
{
    cout << "所有的群信息： " << endl;
    for(auto f : _groupChatRoom){
        GroupChat::getInstance()->showGrouplistInfo(QString::fromStdString(f->name()), QString::number(f->id(), 10));
    }
}

bool Netizen::isLoginSuccess()
{
    if(m_nickname.size() > 0){
        return true;
    }
    return false;
}

string Netizen::sendername(long roomid, long senderid)
{
    for(auto f : _groupChatRoom){
        if(f->id() == roomid){
            return f->sendername(senderid);
        }
    }
    return "none";
}

PrivateChatRoom *Netizen::room(long roomID)
{
    for (auto pcr : _privateChatRooms){
        if(roomID == pcr->id()){
            return pcr;
        }
    }
    return nullptr;
}

long Netizen::friendID(long roomID)
{
    for (auto pcr : _privateChatRooms){
        if(roomID == pcr->id()){
            return pcr->friendID();
        }
    }
}

long Netizen::id() const
{
    return m_id;
}

string Netizen::groupName(long id)
{
    for(auto f : _groupChatRoom){
        if(f->id() == id){
            return f->name();
        }
    }
}

std::string Netizen::nickname() const
{
    return m_nickname;
}


