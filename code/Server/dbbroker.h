#ifndef DBBROKER_H
#define DBBROKER_H

#include <iostream>
#include <mysql/mysql.h>
#include "netizen.h"

class Manager;
class DBBroker
{
public:
    static DBBroker* getInstance();
    ~DBBroker();
    bool connect();
    void initAccount();//初始化所有netizen的账户信息
    long stolong(std::string str);
    void initFrinedInfo(Netizen *netizen);//初始化netizen所有好友信息
    void addFriendTODB(long room,long n1_id,long n2_id);
    void addAccountTODB(long id,std::string pw,std::string name);
private:
    DBBroker();
    MYSQL *_connect;//数据库连接的句柄
    MYSQL_RES *_result;//返回行的查询结果
    MYSQL_ROW m_row;//一次存储一行结果集里面的数据
    static DBBroker* _instance;
};

#endif // DBBROKER_H
