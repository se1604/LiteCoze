#include "groupchatroom.h"
#include "netizen.h"
#include "message.h"
#include "conversion.h"
#include "groupchat.h"

#include <iostream>
#include <cstring>
#include <memory>
#include <sstream>
#include "dbbroker.h"

#include "json/json.h"

using namespace std;


GroupChatroom::GroupChatroom(long id, std::string nickname, std::string avatar):
    m_id{id}, m_nickname{nickname}, m_avatar{avatar}
{

}


void GroupChatroom::addMessage(Message *message)
{
    _messages.push_back(message);
    for (auto n : _netizens){
        if(n->isOnLine()){
            n->sendMessage(message->toJson());
        } else {
            n->addNewOffLineMessage(message);
        }
    }
}

void GroupChatroom::addGroupMember(Netizen *netizen)
{
    _netizens.push_back(netizen);
}

void GroupChatroom::addGroupOwner(Netizen *netizen)
{
    _owner = netizen;
}



long GroupChatroom::id() const
{
    return m_id;
}


bool GroupChatroom::parseJson(Conversion *conversion)
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

    if (conversion->getType() == 9){
        auto gc = new GroupChat();
        m_id = gc->allocateGroupChatRoomID();
        m_nickname = root["groupChatroomNickname"].asString();
        m_avatar = root["groupChatroomAvatar"].asString();
        return true;
    }

    m_id = root["groupChatroomID"].asLargestInt();
    m_nickname = root["groupChatroomNickname"].asString();
    m_avatar = root["groupChatroomAvatar"].asString();
    //测试

    cout << conversion->data() << endl;
    std::cout << "id: " << m_id << ": ";
    std::cout << "nickname: " << m_nickname << std::endl;

    return true;
}

Conversion *GroupChatroom::toJson(int type)
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

Conversion *GroupChatroom::allToJson()
{
    auto conversion = new Conversion();
    Json::Value root, groupChatroomID,groupChatroomNickname, groupChatroomAvatar, memberID, memberNickname, memberAvatar;
    std::ostringstream os;

    root["groupChatroomID"] = m_id;
    root["groupChatroomNickname"] = m_nickname;
    root["groupChatroomAvatar"] = m_avatar;

    int i = 0;
    for(auto n : _netizens){
        memberID[i] = n->id();
        memberNickname[i] = n->nickname();
        memberAvatar[i] = n->avatar();
        i++;
    }

    root["memberID"] = memberID;
    root["memberNickname"] = memberNickname;
    root["memberAvatar"] = memberAvatar;

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

    conversion->setType(10);
    conversion->encode_header();
    conversion->encode_type();
    //cout << _conversion->data() << endl;
    return conversion;
}

void GroupChatroom::dealAddGroupChatroomRequest(Netizen *netizen)
{
    cout << "处理添加群的请求。" << endl;
    if(_owner->isOnLine()){
        netizen->setConversionType(13);
        _owner->send(netizen->toJson(m_id));
    }else {
        _allOffLineRequesters.push_back(netizen);
    }
}

void GroupChatroom::sendAllOffLineAddGroupChatroomRequest()
{
    while (!_allOffLineRequesters.empty()) {
        _allOffLineRequesters.front()->setConversionType(13);
        _netizens[0]->send(_allOffLineRequesters.front()->toJson(m_id));
        _allOffLineRequesters.pop_front();
    }
//    for(auto n : _allOffLineRequesters){
//        n->setConversionType(13);
//        _netizens[0]->send(n->toJson(m_id));
//    }
}

void GroupChatroom::initMemeber(Netizen *netizen)
{
    DBBroker::getInstance()->queryMemberOfGroup(this,netizen);
    printMemeber();
}

void GroupChatroom::addgroupTODB()
{
    long id=this->m_id;
    std::string name=this->m_nickname;
    DBBroker::getInstance()->addGroupTODB(id,name,_netizens[0]->id());
}

void GroupChatroom::printMemeber()
{
    for (auto n:_netizens){
        n->printInfo();
    }
}
