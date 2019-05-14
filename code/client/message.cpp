#include <vector>
#include <sstream>
#include <memory>
#include <iostream>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "message.h"
#include "json/json.h"
#include "privatechatroom.h"
#include "client.h"
#include "netizen.h"
#include "conversion.h"


extern Netizen * netizen;
using namespace std;

Message::Message(std::string content,long senderID, PrivateChatRoom *room):
    m_content{content}, m_senderID{senderID}, _room{room}
{
    _conversion = new Conversion();
    setTime();
    toJson();

    _conversion->setType(1);
    _conversion->encode_header();
    _conversion->encode_type();

    _room->addMessage(this);
}
Message::Message()
{
    m_content = "";
    m_senderID = 0;
    _room = nullptr;
    _conversion = new Conversion();
    _conversion->setType(1);
}




void Message::setTime()
{
    char* sent_time = new char(25);
    time_t tt = time(NULL);//这句返回的只是一个时间cuo
    tm* t= localtime(&tt);

    sprintf(sent_time,"%d-%02d-%02d %02d:%02d:%02d",
            t->tm_year + 1900,
            t->tm_mon + 1,
            t->tm_mday,
            t->tm_hour,
            t->tm_min,
            t->tm_sec);
    string s(sent_time);
    m_time = s;
    //cout << s << " " << s.size();
}

std::string Message::toJson()
{
    Json::Value root;
    std::ostringstream os;

    root["time"] = m_time;
    root["content"] = m_content;
    root["senderID"] = m_senderID;
    root["roomID"] = _room->id();

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

    return jsonStr;
}

bool Message::parseJson(Conversion *conversion)
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
    m_time = root["time"].asString();
    m_content = root["content"].asString();
    m_senderID = root["senderID"].asLargestInt();
    _room = netizen->getPrivateChatRoom(root["roomID"].asLargestInt());
    //测试
    std::cout << "time: " << m_time << ": ";
    std::cout << "content: " << m_content << std::endl;
    //std::cout << "senderID: " << m_senderID << std::endl;
    //std::cout << "roomID: " << _room->id() << std::endl;

    _room->addMessage(this);

    return true;
}

void Message::write()
{
    Client::getInstance()->write(_conversion);
}

//void Message::receive()
//{
//    //parseJson();
//    _room->addMessage(this);
//}

