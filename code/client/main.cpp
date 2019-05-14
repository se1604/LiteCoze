#include <iostream>
#include <thread>
#include "netizen.h"
#include "client.h"
#include "message.h"
#include "conversion.h"

using namespace std;
using boost::asio::ip::tcp;

Netizen * netizen = new Netizen();
int main()
{
    try {
        long id;
        cout << "请输入账号： " ;
        cin >> id;
        cout << endl;
        cin.get();

        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "8080");
        Client *client = Client::getInstance(io_context, endpoints);

//---------------------测试代码开始-----------------------------
        netizen->setId(id);
//        auto n1 = new Netizen{111, "Tom"};
//        auto n2 = new Netizen{222, "Lily"};
//        auto n3 = new Netizen{333, "Amy"};

//        //netizen = n1;

//        n1->addFriend(n2, 111222);
//        n1->addFriend(n3, 111333);


//        //netizen = n1;

//        if (id == 111){
//            netizen = move(n1);
//        }
//        else if (id == 222) {
//            netizen = move(n2);
//        }
//        else if(id == 333){
//            netizen = move(n3);
//        }


        netizen->write();
        //client->do_read_header();

        std::thread t1([&io_context](){ io_context.run(); });
        std::thread t2([&io_context](){ io_context.run(); });
//---------------------测试代码结束-----------------------------

        //netizen->write();
        //n2->write();

//        Message * msg = new Message("hello", netizen->id(), netizen->privateChatRooms()[0]);
//        msg->write();
        long fid;
        //cout << "请选择好友并输入他的账号： " ;
        cin >> fid;
        cout << endl;
        cin.get();

        char line[Conversion::max_body_length + 1];
        while (std::cin.getline(line, Conversion::max_body_length + 1))
        {
            string s(line);
            Message * msg = new Message(s, netizen->id(), netizen->getPrivateChatRoomN(fid));
            msg->write();
        }

        t1.join();
        t2.join();


    } catch (domain_error e) {
        cerr << e.what() << endl;
    }
    return 0;
}
