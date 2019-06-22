#include "groupchatroom.h"
#include "netizen.h"
#include "conversion.h"
#include "groupchat.h"

#include <iostream>
#include <cstring>
#include <memory>
#include <sstream>

#include "json/json.h"
extern Netizen * netizen;

using namespace std;

GroupChatRoom::GroupChatRoom(long id, std::string name, std::string touxiang) : m_id{id}, m_nickname{name}, m_avatar{touxiang}
{

}

void GroupChatRoom::addNetizen(Netizen *netizen)
{
    _netizens.push_back(netizen);
}

Conversion *GroupChatRoom::createNewMessage(std::string content)
{
    auto msg = new Message(content, id());
    addMessage(msg);
    return msg->toJson();
}

void GroupChatRoom::addMessage(Message *mes)
{
    _messages.push_back(mes);
}

bool GroupChatRoom::parseJson(Conversion *conversion)
{
    char* c = conversion->body();
    if (strlen(c) == 0)
        return false;


    JSONCPP_STRING errs;
    Json::Value root, groupChatroomID,groupChatroomNickname, groupChatroomAvatar, memberID, memberNickname, memberAvatar;


    Json::CharReaderBuilder readerBuilder;
    std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());

    bool res;
    res = jsonReader->parse(c, c+strlen(c), &root, &errs);


    if (!res || !errs.empty()) {
        std::cout << "parseJson err. " << errs << std::endl;
    }

    m_id = root["groupChatroomID"].asLargestInt();
    m_nickname = root["groupChatroomNickname"].asString();
    m_avatar = root["groupChatroomAvatar"].asString();

    if (conversion->getType() == 10){
        memberID = root["memberID"];
        memberNickname = root["memberNickname"];
        memberAvatar = root["memberAvatar"];

        for(unsigned int i =0; i < memberID.size(); i++){
            auto f = new Netizen(memberID[i].asLargestInt(), memberNickname[i].asString(), "");
            addNetizen(f);
        }
        GroupChat::getInstance()->showGrouplistInfo(QString::fromStdString(m_nickname), QString::number(m_id, 10));
    }else if(conversion->getType() == 12){
        //long id = root["groupChatroomID"].asLargestInt();
        //std::string name = root["groupChatroomNickname"].asString();
        GroupChat::getInstance()->showFindGroupInfo(QString::fromStdString(m_nickname), QString::number(m_id, 10));
        std::cout << "qunid: " << m_id << ": ";
        std::cout << "nickname: " << m_nickname << std::endl;
        return true;
    }

    //测试


    return true;
}

Conversion *GroupChatRoom::toJson(int type)
{
    auto conversion = new Conversion();
    Json::Value root;
    std::ostringstream os;

    root["groupChatroomID"] = m_id;
    root["groupChatroomNickname"] = m_nickname;
    root["groupChatroomAvatar"] = m_avatar;

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

    conversion->body_length(jsonStr.length());
    //_conversion->m_body_length = jsonStr.length();
    //memcpy(data_ + header_length, c, body_length_);
    strcpy(conversion->body(),c);
    conversion->setType(type);
    conversion->encode_type();
    conversion->encode_header();

    //cout << _conversion->data() << endl;

    return conversion;
}

long GroupChatRoom::id() const
{
    return m_id;
}

std::string GroupChatRoom::name() const
{
    return m_nickname;
}


std::string GroupChatRoom::touxiang() const
{
    return m_avatar;
}

