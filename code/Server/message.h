#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>

class Conversion;
class PrivateChatRoom;
class Message
{
public:
    friend class Conversion;
    Message();
    bool parseJson(Conversion *conversion, long senderID);
    Conversion * toJson();

    long roomID() const;
    long senderID() const;

private:
    std::string m_time;//发送消息的时间
    std::string m_content;//消息的内容
    long m_senderID;//发送消息的人的id
    long m_roomID;//消息所属的房间
    Conversion *_conversion;
};

#endif // MESSAGE_H
