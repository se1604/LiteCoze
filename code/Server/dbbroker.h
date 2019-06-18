#ifndef DBBROKER_H
#define DBBROKER_H

#include <iostream>
#include <mysql/mysql.h>
#include "manager.h"
#include "netizen.h"

class DBBroker
{
public:
    static DBBroker* getInstance();
    ~DBBroker();
    bool connect();
    void initAccount();
    long stolong(std::string str);
private:
    DBBroker();
    MYSQL *_connect;//数据库连接的句柄
    MYSQL_RES *_result;//返回行的查询结果
    MYSQL_ROW m_row;//一次存储一行结果集里面的数据
    static DBBroker* _instance;
};

#endif // DBBROKER_H
