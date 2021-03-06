#include "netizen.h"
#include "conversion.h"
#include <iostream>
#include <cstring>
#include <memory>
#include <sstream>
#include "privatechatroom.h"
#include "client.h"
#include <QString>

#include "json/json.h"
using namespace std;

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

    friendID = root["friendID"];
    friendNickname = root["friendNickname"];
    roomID = root["roomID"];


    for(unsigned int i =0; i < friendID.size(); i++){
        auto f = new Netizen(friendID[i].asLargestInt(), friendNickname[i].asString(), "");
        addFriend(f, roomID[i].asLargestInt());
    }

    m_id = root["id"].asLargestInt();
    m_nickname = root["nickname"].asString();
    //测试
    std::cout << "id: " << m_id << ": ";
    std::cout << "password: " << m_password << std::endl;
    std::cout << "nickname: " << m_nickname << std::endl;
    printInfo();


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

void Netizen::addFriend(Netizen *f, long roomID)
{
    _friends.push_back(f);
    f->_friends.push_back(this);
    PrivateChatRoom *room = new PrivateChatRoom(roomID, this, f);
    _privateChatRooms.push_back(room);
    f->_privateChatRooms.push_back(room);
    cout << m_nickname << "与" << f->m_nickname << "成为朋友" << endl << endl;
}

void Netizen::printInfo(){
    cout << "所有的好友信息： " << endl;
    for(auto f : _friends){
        Client::getInstance()->showAccountInfo(QString::fromStdString(f->m_nickname), f->m_id);
    }
}

bool Netizen::isLoginSuccess()
{
    if(m_nickname.size() > 0){
        return true;
    }
    return false;
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
