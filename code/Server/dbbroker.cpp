#include "dbbroker.h"
#include <sstream>
#include "accountmanager.h"

DBBroker* DBBroker::_instance = nullptr;

DBBroker::DBBroker()
{
    _connect=mysql_init(NULL);
    bool flag=connect();
    if(flag==true){
        std::cout<<"连接数据库成功"<<std::endl;
    }
}

DBBroker *DBBroker::getInstance()
{
    if(_instance == nullptr)
        _instance = new DBBroker();
    return _instance;
}

DBBroker::~DBBroker()
{
    if(_connect){
        mysql_close(_connect);
    }
}

bool DBBroker::connect()
{
    _connect = mysql_real_connect(_connect,"localhost",
                                  "","root","LiteCoze",0,NULL,0);
    if(!_connect){
        std::cout<<"连接数据库失败：error occurs "<<mysql_error(_connect);
        return false;
    }
    return true;
}

void DBBroker::initAccount()
{
    unsigned num_clo;
    long id=0;
    int num_row;
    std::string pw,name;
    mysql_query(_connect, "SELECT * FROM netizen");
    _result = mysql_store_result(_connect);//将查询到的结果集储存到result中
    num_clo = mysql_num_fields(_result); //将结果集列数存放到num中
    num_row=mysql_num_rows(_result);

    std::cout<<num_row;
    while ((m_row = mysql_fetch_row(_result)))  //遇到最后一行，则中止循环
    {
        for (unsigned i=0; i < num_clo;i++) //利用for循环，输出该行的每一列
        {
            if(m_row[i]){
                if(i==0){
                    std::string temp=m_row[i];
                    id=stolong(temp);
                }
                else if(i==1)
                    pw=m_row[i];
                else if(i==2)
                    name=m_row[i];
            }
        }
        auto netizen=new Netizen(id,pw,name);
    }
    mysql_free_result(_result); //释放结果集所占用的内存
    //mysql_close(_connect);
}

long DBBroker::stolong(std::string str){
    long result;
    std::istringstream is(str);
    is>>result;
    return result;
}

std::string DBBroker::longToS(long id)
{
    std::ostringstream os;
    os<<id;
    std::string result;
    std::istringstream is("g"+os.str());
    is>>result;
    return result;
}

void DBBroker::initFrinedInfo(Netizen *netizen)
{
    long temp_id=netizen->id();
    unsigned num_clo;
    long room_id=0;
    long netizen1_id=0;
    long netizen2_id=0;

    mysql_query(_connect, "SELECT * FROM privateroom");
    _result = mysql_store_result(_connect);
    num_clo = mysql_num_fields(_result);

    while ((m_row = mysql_fetch_row(_result)))
    {
        for (unsigned i=0; i < num_clo;i++)
        {
            if(m_row[i]){
                if(i==0){
                    std::string temp=m_row[i];
                    room_id=stolong(temp);
                }
                else if(i==1){
                    std::string temp=m_row[i];
                    netizen1_id=stolong(temp);
                }
                else if(i==2){
                    std::string temp=m_row[i];
                    netizen2_id=stolong(temp);
                }
            }
        }
        if(netizen1_id==temp_id)
        {
            auto n=new Netizen();
            n=AccountManager::getInstance()->getNetizen(netizen2_id);
            if(netizen->isAlreadyFriend(n)==false)
                netizen->addFriend(n,room_id);
        }else if(netizen2_id==temp_id){
            auto n=new Netizen();
            n=AccountManager::getInstance()->getNetizen(netizen1_id);
            if(netizen->isAlreadyFriend(n)==false)
                netizen->addFriend(n,room_id);
        }
    }
    mysql_free_result(_result);
    //    mysql_close(_connect);
}

void DBBroker::initGroupInfo(Netizen *netizen)
{
    char sql[1024]={0};
    unsigned num_clo;
    long temp_id=netizen->id();
    long room_id=0;
    long netizen_id=0;
    std::string name;

    snprintf(sql,sizeof (sql),"select grouproom.id,grouproom.name from grouproom,netizen_grouproom where netizen_grouproom.netizen_id='%ld' and netizen_grouproom.grouproom_id=grouproom.id",temp_id);

    mysql_query(_connect, sql);
    _result = mysql_store_result(_connect);
    num_clo = mysql_num_fields(_result);

    while ((m_row = mysql_fetch_row(_result)))
    {
        for (unsigned i=0; i < num_clo;i++)
        {
            if(m_row[i]){
                if(i==0){
                    std::string temp=m_row[i];
                    room_id=stolong(temp);
                }else if(i==1){
                    name=m_row[i];
                }
            }
        }
        std::cout<<temp_id<<"的群信息"<<std::endl;
        std::cout<<"群号"<<room_id<<"群名"<<name<<std::endl;//测试代码
        queryMemberOfGroup(room_id);
    }
    mysql_free_result(_result);
}

void DBBroker::queryMemberOfGroup(long id)
{
    unsigned num;
    char sql[1024]={0};
    long netizen_id=0;
    std::string s=longToS(id);

    snprintf(sql,sizeof (sql),"select * from %s",s.c_str());
    mysql_query(_connect,sql);
    _result=mysql_store_result(_connect);
    num=mysql_num_fields(_result);

    while ((m_row = mysql_fetch_row(_result)))
    {
        for (unsigned i=0; i < num;i++)
        {
            if(m_row[i]){
                std::string temp=m_row[i];
                netizen_id=stolong(temp);
            }
        }
        auto n=new Netizen();
        n=AccountManager::getInstance()->getNetizen(netizen_id);
        n->printInfo();
    }
    mysql_free_result(_result);
}

void DBBroker::addFriendTODB(long room, long n1_id, long n2_id)
{
    char sql[1024]={0};
    snprintf(sql,sizeof (sql),"insert into privateroom"
                              "(id,netizen1_id,netizen2_id) values('%ld',"
                              "'%ld','%ld')",room,n1_id,n2_id);
    if(mysql_query(_connect,sql)){
        std::cout<<"添加好友失败"<<std::endl;
    }else {
        std::cout<<"添加好友成功"<<std::endl;
    }
}

void DBBroker::addAccountTODB(long id, std::string pw, std::string name)
{
    char sql[1024]={0};

    snprintf(sql,sizeof (sql),"insert into netizen"
                              " (id,password,nickname) values('%ld',"
                              "'%s','%s')",id,pw.c_str(),name.c_str());
    if(mysql_query(_connect,sql)){
        std::cout<<"注册账户失败"<<std::endl;
    }else {
        std::cout<<"注册账户成功"<<std::endl;
    }
}

void DBBroker::addGroupTODB(long id, std::string name,long netizen_id)
{
    char sql_1[1024]={0};

    snprintf(sql_1,sizeof (sql_1),"insert into grouproom"
                                  " (id,name) values('%ld',"
                                  "'%s')",id,name.c_str());
    if(mysql_query(_connect,sql_1)){
        std::cout<<"创建群失败"<<std::endl;
    }else {
        std::cout<<"创建群成功"<<std::endl;
    }
    addGroupInfo(id,netizen_id);
    createMemberList(id);
    addMember(id,netizen_id);
}

void DBBroker::createMemberList(long id)
{
    char sql_3[1024]={0};
    std::string s=longToS(id);
    snprintf(sql_3,sizeof (sql_3),"create table %s(netizen_id BIGINT,foreign key (netizen_id) references netizen(id))",s.c_str());
    if(mysql_query(_connect,sql_3)){
        std::cout<<"创建失败"<<std::endl;
    }else {
        std::cout<<"创建成功"<<std::endl;
    }
}

void DBBroker::addGroupInfo(long id, long netizen_id)
{
    char sql_2[1024]={0};
    snprintf(sql_2,sizeof (sql_2),"insert into netizen_grouproom"
                                  "(grouproom_id,netizen_id) values ("
                                  "'%ld','%ld')",id,netizen_id);
    if(mysql_query(_connect,sql_2)){
        std::cout<<"插入失败"<<std::endl;
    }else {
        std::cout<<"插入成功"<<std::endl;
    }
}

void DBBroker::addMember(long id, long netizen_id)
{
    char sql[1024]={0};
    std::string s=longToS(id);
    snprintf(sql,sizeof (sql),"insert into %s (netizen_id) values ('%ld')",s.c_str(),netizen_id);
    if(mysql_query(_connect,sql)){
        std::cout<<"插入失败"<<std::endl;
    }else {
        std::cout<<"插入成功"<<std::endl;
    }
}
