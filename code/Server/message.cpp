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
#include "netizen.h"
#include "conversion.h"


extern Netizen * netizen;
using namespace std;

Message::Message(std::string content,long senderID, PrivateChatRoom *room):
    m_content{content}, m_senderID{senderID}, _room{room}
{
    s_conversion = new Conversion();
    //setTime();
    //toJson();
    //_room->addMessage(this);
    //Client::getInstance()->write(this);
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

    s_conversion->m_body_length = jsonStr.length();
    //memcpy(data_ + header_length, c, body_length_);
    strcpy(s_conversion->body(),c);
    s_conversion->encode_header();

    //cout << s_conversion->m_data << endl;

    return jsonStr;
}

bool Message::parseJson(Netizen *netizen, Conversion *conversion)
{
    r_conversion = conversion;
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
    _room->printInfo();

    return true;
}

//void Message::receive()
//{
//    _room->addMessage(this);
//}
