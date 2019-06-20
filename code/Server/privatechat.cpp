#include "privatechat.h"

#include <iostream>
#include <fstream>

#include "accountmanager.h"

using namespace std;

PrivateChat::PrivateChat()
{

}

void PrivateChat::initFriend()
{
    AccountManager::getInstance()->initFriend();
}

long PrivateChat::allocatePrivateChatRoomID()
{
    long number;
    ifstream ifs("../allocatePrivateroomID");
    if (ifs.fail())
    {
        cout<<"打开文件错误!"<<endl;
        exit(0);
    }
    cout<<"打开文件成功!"<<endl;
    ifs >> number;
    cout<<number<<endl;
    ifs.close();

    ofstream ofs("../allocatePrivateroomID");
    if (ofs.fail())
    {
        cout<<"打开文件错误!"<<endl;
        exit(0);
    }
    cout<<"打开文件成功!"<<endl;

    number++;
    ofs<<number;
    ofs.close();
    return number;
}
