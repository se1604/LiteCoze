#include "message.h"
#include "conversion.h"
#include "privatechatroom.h"
#include <iostream>
#include <cstring>
#include <memory>
#include <sstream>

#include "json/json.h"
using namespace std;

Message::Message()
{
    m_time = "";
    m_content = "";
    m_senderID = 0;
}

bool Message::parseJson(Conversion *conversion, long senderID){
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
    m_senderID = senderID;
    m_roomID = root["roomID"].asLargestInt();
    //测试
    std::cout << "time: " << m_time << ": ";
    std::cout << "content: " << m_content << std::endl;
    std::cout << "senderID: " << m_senderID << std::endl;
    std::cout << "roomID: " << m_roomID << std::endl;

    return true;
}

Conversion *Message::toJson()
{
//    if (_conversion)
//        return _conversion;

    _conversion = new Conversion();
    Json::Value root;
    std::ostringstream os;

    root["time"] = m_time;
    root["content"] = m_content;
    root["roomID"] = m_roomID;
    root["senderID"] = m_senderID;

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
    _conversion->setType(3);
    _conversion->encode_type();
     _conversion->encode_header();

    //cout << _conversion->data() << endl;

    return _conversion;
}

long Message::roomID() const
{
    return m_roomID;
}

long Message::senderID() const
{
    return m_senderID;
}
