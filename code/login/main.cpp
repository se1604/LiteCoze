//19.6.18 duHongpeng
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include <thread>
#include "netizen.h"
#include "client.h"
#include "clientui.h"
#include "message.h"
#include "loginUI.h"
#include "searchui.h"

Netizen * netizen;
using namespace std;

//void selectFriend();
//int startSearch(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    boost::asio::io_context io_context;
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("127.0.0.1", "8080");
    Client *client = Client::getInstance(io_context, endpoints);

//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QGuiApplication app(argc, argv);

    qmlRegisterType<LogInUI>("loginUI",1,0,"MyLogin");
    qmlRegisterType<ClientUI>("clientUI",1,0,"MyClient");
    qmlRegisterType<SearchUi>("searchUI", 1, 0, "MySearch");      ////////////

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/Login.qml")));

//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

    boost::asio::post(io_context,[&argc, &argv](){
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QGuiApplication app(argc, argv);
        QQmlApplicationEngine engine;
        engine.load(QUrl(QStringLiteral("qrc:/Search.qml")));

        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//        QObject::connect(Client::getInstance()->get, SIGNAL(start()));

        return app.exec();
    });
    std::thread t1([&io_context](){ io_context.run(); });
    std::thread t2([&io_context](){ io_context.run(); });
    t1.join();
    t2.join();
    return 0;

    //return app.exec();
}

//void selectFriend(){
//    while (!(Client::getInstance()->isLoginSuccess())) {}
//    long fid;
//    cout << "请输入好友账号： " << endl;
//    cin >> fid;
//    ClientUI::getInstance()->selectFriend(fid);

//    cin.get();

//    cout << "输入聊天内容： " << endl;

//    char line[Conversion::max_body_length + 1];
//    while (std::cin.getline(line, Conversion::max_body_length + 1))
//    {
//        string s(line);
//        ClientUI::getInstance()->sendNewMessage(s);
//    }
//}

//int startSearch(int argc, char *argv[]){
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QGuiApplication app(argc, argv);
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/Login.qml")));

//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    return app.exec();
//}

