#include "conversion.h"
#include <vector>
#include <sstream>
#include <memory>
#include <iostream>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

Conversion::Conversion():
    m_body_length{0}, m_type{0}
{

}
const char *Conversion::data() const
{
    return m_data;
}

char *Conversion::data()
{
    return m_data;
}
const char *Conversion::body() const
{
    return m_data + header_length + type_length;
}

char *Conversion::body()
{
    return m_data + header_length +type_length;
}

const char *Conversion::type() const
{
    return m_data + header_length;
}

char *Conversion::type()
{
    return m_data + header_length;
}

std::size_t Conversion::body_length() const
{
    return m_body_length;
}

void Conversion::body_length(std::size_t new_length)
{
    m_body_length = new_length;
    if (m_body_length > max_body_length)
        m_body_length = max_body_length;
}
std::size_t Conversion::length() const
{
    return header_length + type_length+ m_body_length;
}


bool Conversion::decode_header()
{
    char header[header_length + 1] = "";
    std::strncat(header, m_data, header_length);//把m_data所指字符串的前header_length个字符添加到header结尾处，覆盖header结尾处的'/0'，实现字符串连接。
    m_body_length = std::atoi(header) - type_length;
    if (m_body_length > max_body_length)
    {
        m_body_length = 0;
        return false;
    }
    return true;
}

void Conversion::encode_header()
{
    char header[header_length + 1] = "";
    std::sprintf(header, "%4d", static_cast<int>(m_body_length + type_length));//将m_body_length转换为4位右对齐的整型（高位自动添零）后赋给header
    std::memcpy(m_data, header, header_length);//memcpy函数的功能是从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中

}
int Conversion::decode_type()
{
    char type[type_length + 1] = "";
    std::strncat(type, m_data + header_length, type_length);//把m_data所指字符串的前type_length个字符添加到type结尾处，覆盖type结尾处的'/0'，实现字符串连接。
    m_type = std::atoi(type);
    if (m_type >= 10)
    {
        m_type = 0;
    }
    return m_type;
}

void Conversion::encode_type()
{
    char type[type_length + 1] = "";
    std::sprintf(type, "%1d", m_type);//将m_type转换为1位右对齐的整型（高位自动添零）后赋给type
    std::memcpy(m_data + header_length, type, type_length);//memcpy函数的功能是从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中

}
void Conversion::setType(int type)
{
    m_type = type;
}

int Conversion::getType()
{
    return m_type;
}

