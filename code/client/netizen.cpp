#include "netizen.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <cstring>

#include "privatechatroom.h"
#include "json/json.h"
#include "conversion.h"
#include "client.h"

using namespace std;

Netizen::Netizen(long id, string nickname):
    m_id{id}, m_nickname{nickname}, _conversion{nullptr}
{
    _conversion = new Conversion();
    _conversion->setType(2);
}

void Netizen::addFriend(Netizen *f, long roomID)
{
    _friends.push_back(f);
    f->_friends.push_back(this);
    auto room = new PrivateChatRoom(roomID, this, f);
    _privateChatRooms.push_back(room);
    f->_privateChatRooms.push_back(room);
    cout << m_nickname << "与" << f->m_nickname << "成为朋友" << endl << endl;
}
void Netizen::printInfo()
{
    cout << m_nickname << "的朋友有：";
    for(auto f : _friends)
    {
        cout << f->m_nickname << ' ' ;
    }
    cout << endl << endl;
}

std::vector<PrivateChatRoom *> Netizen::privateChatRooms() const
{
    return _privateChatRooms;
}

PrivateChatRoom *Netizen::getPrivateChatRoom(long roomID)
{
    for (auto pr: _privateChatRooms){
        if(pr->id() == roomID)
            return pr;
    }
    return nullptr;
}

PrivateChatRoom *Netizen::getPrivateChatRoomN(long nitizenID)
{
    for (auto pr : _privateChatRooms){
        if((pr->_netizen1->id() == nitizenID) ||
                (pr->_netizen2->id() == nitizenID)){
            return pr;
        }
    }
    return  nullptr;
}

long Netizen::id() const
{
    return m_id;
}

std::string Netizen::toJson()
{
    Json::Value root;
    std::ostringstream os;

    root["id"] = m_id;
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

    //cout << _conversion->data() << endl;
    _conversion->encode_header();
    _conversion->encode_type();

    //cout << _conversion->data() << endl;

    return jsonStr;
}

long Netizen::parseJson(Conversion *conversion)
{
    char* c = conversion->body();
    if (strlen(c) == 0)
        return 0;


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
    m_nickname = root["nickname"].asString();
    //测试
    std::cout << "id: " << m_id << ": ";
    std::cout << "nickname: " << m_nickname << std::endl;
    if (root["roomID"].asLargestInt() == 0)
        return 0;

    return root["roomID"].asLargestInt();
}

void Netizen::write()
{
    toJson();
    Client::getInstance()->write(_conversion);
}

void Netizen::setId(long id)
{
    m_id = id;
}
