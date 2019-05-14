#include "netizen.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <cstring>

#include "json/json.h"
#include "manager.h"
#include "privatechatroom.h"
#include "network.h"
#include "conversion.h"

using namespace std;
extern boost::asio::io_context io_context;

Netizen::Netizen(long id, string nickname):
    m_id{id}, m_nickname{nickname}
{
    Manager* manager = Manager::getInstance();
    manager->addNetizen(this);
    _conversion = new Conversion();
    _conversion->setType(2);
    //toJson();
}
Netizen::Netizen()
{
    m_id = 0;
    m_nickname = "";
    _conversion = new Conversion();
    _conversion->setType(2);
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

PrivateChatRoom *Netizen::getPrivateChatRoom(long id)
{
    for (auto pr: _privateChatRooms){
        if(pr->id() == id)
            return pr;
    }
    return nullptr;
}

long Netizen::getPrivateChatRoomID(Netizen *f)
{
    if(f->m_id == m_id)
    {
        return 0;
    }
    for (auto pr : _privateChatRooms){
        if(pr->_netizen1->m_id == f->m_id || pr->_netizen2->m_id == f->m_id)
        {
            return pr->id();
        }
    }
    return  -1;
}

void Netizen::setNetwork(boost::asio::ip::tcp::socket socket)
{
    _network = new Network(move(socket), this);
    _network->do_read_header();
}

void Netizen::sendAllFriends()
{
    for (auto n : _friends){
        n->toJson(this);
        _network->write(n->_conversion);
    }
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
std::string Netizen::toJson(Netizen *netizen)
{
    Json::Value root;
    std::ostringstream os;

    root["id"] = m_id;
    root["nickname"] = m_nickname;

    long i = getPrivateChatRoomID(netizen);
    root["roomID"] = i;

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

    return jsonStr;
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
    m_nickname = root["nickname"].asString();
    //测试
    std::cout << "id: " << m_id << ": ";
    std::cout << "nickname: " << m_nickname << std::endl;

    return true;
}
