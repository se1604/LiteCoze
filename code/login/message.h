#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
class PrivateChatRoom;
class Conversion;

class Message
{
public:
    Message(std::string content, long roomID);
    Message();
    Conversion* toJson();
    bool parseJson(Conversion * conversion);
private:
    void setTime();

    std::string m_time;//发送消息的时间
    std::string m_content;//消息的内容
    //PrivateChatRoom *_room;//消息所属的房间
    long m_roomID;
    Conversion *_conversion;
};

#endif // MESSAGE_H
