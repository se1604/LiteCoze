#ifndef CONVERSION_H
#define CONVERSION_H

#include <string>

class Conversion
{
public:
    Conversion();
    enum { header_length = 4 };
    enum { type_length = 2 };
    enum { max_body_length = 512 };

    const char* data() const;
    char* data();
    const char* type() const;
    char* type();
    const char* body() const;
    char* body();
    std::size_t body_length() const;
    void body_length(std::size_t new_length);
    std::size_t length() const;
    bool decode_header();
    void encode_header();

    int decode_type();
    void encode_type();
    void setType(int type);
    int getType();

private:
    char m_data[header_length + max_body_length];
    std::size_t m_body_length;
    int m_type;//1为Netizen登录信息，2为普通Netizen信息，3为Message
    //4为查找网民的Netizen信息（id）,5为注册请求, 6为返回查找的Netizen信息,
    //7为请求添加好友的Netizen信息,8为接受添加好友的Netizen信息
    //11为查找群的GroupChatroom信息，12为返回的查找群的GroupChatroom信息
    //13为请求加群的GroupChatroom信息，14为接受添加群的GroupChatroom信息
};

#endif // CONVERSION_H
