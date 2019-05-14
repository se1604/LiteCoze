#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include "json/json.h"

class PrivateChatRoom;
class Conversion;
class Netizen;

class Message
{
public:
    friend class Network;
    friend class PrivateChatRoom;//测试printInfo()
    Message(std::string content=" ",long senderID=0, PrivateChatRoom *room=nullptr);

    std::string toJson();//将Message对象转换为json字符串
    bool parseJson(Netizen* netizen, Conversion *conversion);//解析json字符串
    //void receive();
private:
    std::string m_time;//发送消息的时间
    std::string m_content;//消息的内容
    long m_senderID;//发送消息的人的id
    PrivateChatRoom *_room;//消息所属的房间

    Conversion *s_conversion;
    Conversion *r_conversion;
};

#endif // MESSAGE_H
