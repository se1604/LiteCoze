#include <iostream>
#include <thread>
#include "netizen.h"
#include "client.h"
#include "clientui.h"
#include "message.h"
#include "loginUI.h"

Netizen * netizen;
using namespace std;

void selectFriend();
void findNetizen();

int main()
{
    try {
        long id;
        cout << "请输入账号： " ;
        cin >> id;
        cout << endl;

        string password;
        cout << "请输入密码： " ;
        cin >> password;
        cout << endl;

        cin.get();
        //netizen = new Netizen(id, password);


        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "8080");
        Client *client = Client::getInstance(io_context, endpoints);


        LogInUI* logInUI = new LogInUI();
        ClientUI* clientUI = ClientUI::getInstance();
        logInUI->logIn(id, password);
//---------------------------------------------------------------
        boost::asio::post(io_context,findNetizen);
//---------------------------------------------------------------
        std::thread t1([&io_context](){ io_context.run(); });
        std::thread t2([&io_context](){ io_context.run(); });

        t1.join();
        t2.join();

    } catch (domain_error e) {
        cout << e.what() << endl;
    }
    return 0;
}


void selectFriend(){
    while (!(Client::getInstance()->isLoginSuccess())) {}
    long fid;
    cout << "请输入好友账号： " << endl;
    cin >> fid;
    ClientUI::getInstance()->selectFriend(fid);

    cin.get();

    cout << "输入聊天内容： " << endl;

    char line[Conversion::max_body_length + 1];
    while (std::cin.getline(line, Conversion::max_body_length + 1))
    {
        string s(line);
        ClientUI::getInstance()->sendNewMessage(s);
    }
}
//------------------------------------------------------------
void findNetizen(){
    long fid;
    cout << "请输入需要查找的账号： " << endl;
    cin >> fid;
    cin.get();
    Client::getInstance()->findNetizen(fid);
    Client::getInstance()->addFriend(fid);

    selectFriend();
}
//-------------------------------------------------------------
