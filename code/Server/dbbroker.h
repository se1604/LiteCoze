#ifndef DBBROKER_H
#define DBBROKER_H

#include <iostream>
#include <mysql/mysql.h>
#include "netizen.h"

class AccountManager;
class DBBroker
{
public:
    static DBBroker* getInstance();
    ~DBBroker();
    bool connect();//连接数据库
    void initAccount();//初始化所有netizen的账户信息
    long stolong(std::string str);//string转化为long
    std::string longToS(long id);
    void initFrinedInfo(Netizen *netizen);//初始化netizen所有好友信息
    void initGroupInfo(Netizen *netizen);//初始化netizen的群列表
    void queryMemberOfGroup(GroupChatroom *grouproom,Netizen* netizen);//查询一个群里面的所有群成员
    void addFriendTODB(long room,long n1_id,long n2_id);//添加好友关系到数据库
    void addAccountTODB(long id,std::string pw,std::string name);//添加注册的账户信息到数据库
    void addGroupTODB(long id,std::string name,long netizen_id);//创建一个群，添加到数据库
    void createMemberList(long id);
    void addGroupInfo(long id,long netizen_id);
    void addMember(long id,long netizen_id);
private:
    DBBroker();
    MYSQL *_connect;//数据库连接的句柄
    MYSQL_RES *_result;//返回行的查询结果
    MYSQL_ROW m_row;//一次存储一行结果集里面的数据
    //std::vector<Netizen*> _netizens;
    static DBBroker* _instance;
};

#endif // DBBROKER_H
