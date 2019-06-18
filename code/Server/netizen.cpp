#include "netizen.h"
#include "manager.h"
#include "conversion.h"
#include "privatechatroom.h"
#include "message.h"
#include <iostream>
#include <cstring>
#include <memory>
#include <sstream>
#include "networktransmission.h"

#include "json/json.h"

using namespace std;

Netizen::Netizen(long id,string password, std::string nickname):
    m_id{id},m_password{password}, m_nickname{nickname}
{
    _networkTransmission = nullptr;
    Manager* manager = Manager::getInstance();
    manager->addNetizen(this);
    _conversion = new Conversion();
    _conversion->setType(2);
    //toJson();
}

Netizen::Netizen()
{
    _networkTransmission = nullptr;
    m_id = 0;
    m_nickname = "";
    _conversion = new Conversion();
    _conversion->setType(2);
}

Netizen::~Netizen()
{
    if (_conversion){
        delete _conversion;
        _conversion = nullptr;
    }
}

void Netizen::sendAllOffLineMessages()
{
    for(auto pcr : _privateChatRooms){
        pcr->sendAllOffLineMessages(this);
    }
}

void Netizen::sendAllOffLineFriendRequest()
{
    for(auto f : _friendRequests){
        f->setConversionType(7);
        _networkTransmission->send(f->toJson());
    }
}

void Netizen::sendMessage(Conversion *conversion)
{
    _networkTransmission->send(conversion);
}

void Netizen::addNewMessageToRoom(Message *message)
{
    for(auto prc : _privateChatRooms){
        if(message->roomID() == prc->id()){
            prc->addMessage(message);
        }
    }
}

void Netizen::addFriendRequest(Netizen *netizen)
{
    if(isOnLine()){
        netizen->setConversionType(7);
        _networkTransmission->send(netizen->toJson());
    } else {
        _friendRequests.push_back(netizen);
    }
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

void Netizen::acceptAddFriendRequest(Netizen *f)
{
    long roomID = Manager::getInstance()->allocateRoomID();
    addFriend(f, roomID);
    if(_networkTransmission){
        f->setConversionType(8);
       _networkTransmission->send(f->toJson(roomID));
    }
    if(f->_networkTransmission){
        setConversionType(8);
        f->_networkTransmission->send(toJson(roomID));
    }
}

bool Netizen::parseJson(Conversion *conversion)
{
    char* c = conversion->body();
    if (strlen(c) == 0)
        return false;


    JSONCPP_STRING errs;
    Json::Value root;


    Json::CharReaderBuilder readerBuilder;
    std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());

    bool res;
    res = jsonReader->parse(c, c+strlen(c), &root, &errs);


    if (!res || !errs.empty()) {
        std::cout << "parseJson err. " << errs << std::endl;
    }
    m_id = root["id"].asLargestInt();
    m_password = root["password"].asString();
    m_nickname = root["nickname"].asString();
    //测试
    std::cout << "id: " << m_id << ": ";
    std::cout << "password: " << m_password << std::endl;
    std::cout << "nickname: " << m_nickname << std::endl;

    return true;
}

Conversion* Netizen::toJson()
{
    Json::Value root, friendID, friendNickname, roomID;
    std::ostringstream os;

    root["id"] = m_id;
    root["nickname"] = m_nickname;

    if (_conversion->getType() == 2){
        int i = 0;
        for (auto pcr : _privateChatRooms){
            auto f = pcr->getFriend(this);
            friendID[i] = f->m_id;
            friendNickname[i] = f->m_nickname;
            roomID[i] = pcr->id();
            i++;
        }
        root["friendID"] = friendID;
        root["friendNickname"] = friendNickname;
        root["roomID"] = roomID;
    }


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
    root["nickname"] = m_nickname;
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

bool Netizen::checkAccount(Netizen *netizen, NetworkTransmission* networkTransmission)
{
    if((m_id == netizen->m_id) && (m_password == netizen->m_password)){
        _networkTransmission = networkTransmission;
        return true;
    }
    return false;
}

bool Netizen::findNetizen(Netizen *netizen)
{
    if(m_id == netizen->m_id){
        return true;
    }
    return false;
}

void Netizen::printInfo(){
    cout << "id: " << m_id << "昵称: " << m_nickname << endl;
}

long Netizen::id() const
{
    return m_id;
}

bool Netizen::isOnLine()
{
    if(_networkTransmission == nullptr){
        return false;
    }
    return true;
}

void Netizen::offLine()
{
    _networkTransmission = nullptr;
}


void Netizen::setConversionType(int type)
{
    _conversion->setType(type);
}
