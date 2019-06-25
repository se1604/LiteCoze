#include "message.h"
#include "conversion.h"
#include <iostream>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "json/json.h"
#include <sstream>
#include <memory>
#include "privatechatroom.h"
#include "netizen.h"
#include "client.h"

using namespace std;
extern Netizen * netizen;


Message::Message(std::string content,PrivateChatRoom *room):
    m_content{content}, _room{room}
{
    _conversion = new Conversion();
    setTime();
    //toJson();

    _conversion->setType(3);
//    _conversion->encode_header();
    _conversion->encode_type();

    //_room->addMessage(this);
}
Message::Message()
{

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

Conversion *Message::toJson()
{
    Json::Value root;
    std::ostringstream os;

    root["time"] = m_time;
    root["content"] = m_content;
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
    _conversion->encode_header();

    //cout << _conversion->data() << endl;

    return _conversion;
}

bool Message::parseJson(Conversion * conversion){
    _conversion = conversion;
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
    long roomID = root["roomID"].asLargestInt();

    _room = netizen->room(roomID);
    _room->addMessage(this);

    long friendID = netizen->friendID(roomID);

    Client::getInstance()->showFriendMsg(QString::number(friendID, 10), QString::fromStdString(m_content));

    //测试
    std::cout << "time: " << m_time << ": ";
    std::cout << "content: " << m_content << std::endl;
    std::cout << "roomID: " << roomID << std::endl;

    return true;
}
