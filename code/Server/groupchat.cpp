#include "groupchat.h"

#include <iostream>
#include <fstream>

using namespace std;

GroupChat::GroupChat()
{

}

long GroupChat::allocateGroupChatRoomID()
{
    long number;
    ifstream ifs("../allocateGrouproomID");
    if (ifs.fail())
    {
        cout<<"打开文件错误!"<<endl;
        exit(0);
    }
    cout<<"打开文件成功!"<<endl;
    ifs >> number;
    cout<<number<<endl;
    ifs.close();

    ofstream ofs("../allocateGrouproomID");
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
