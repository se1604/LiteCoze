#include "dbbroker.h"
#include <sstream>

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
       // Manager::getInstance()->printInfo();
    }

    mysql_free_result(_result); //释放结果集所占用的内存
    mysql_close(_connect);
}

long DBBroker::stolong(std::string str){
    long result;
    std::istringstream is(str);
    is>>result;
    return result;
}
