#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include "json/json.h"

class PrivateChatRoom;
class Conversion;
class Message
{
public:
    friend class Client;
    Message(std::string content,long senderID, PrivateChatRoom *room);
    Message();

    void setTime();
    std::string toJson();//将Message对象转换为json字符串
    bool parseJson(Conversion *conversion);//解析json字符串
    //void receive();
    void write();

private:
    std::string m_time;//发送消息的时间
    std::string m_content;//消息的内容
    long m_senderID;//发送消息的人的id
    PrivateChatRoom *_room;//消息所属的房间

    Conversion *_conversion;
};

#endif // MESSAGE_H
