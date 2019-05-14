#include <iostream>
#include "manager.h"
#include "netizen.h"
#include "server.h"

using boost::asio::ip::tcp;
using namespace std;

boost::asio::io_context io_context;
int main()
{
    try {
        tcp::endpoint endpoint(tcp::v6(), std::atoi("8080"));

        Server* server = Server::getInstance(io_context, endpoint);

        Manager* manager = Manager::getInstance();
//---------------------测试代码开始-----------------------------
        auto n1 = new Netizen{111, "Tom"};
        auto n2 = new Netizen{222, "Lily"};
        auto n3 = new Netizen{333, "Amy"};
        n1->addFriend(n2, 111222);
        n1->addFriend(n3, 111333);

        manager->printInfo();

        n1->printInfo();
        n2->printInfo();
        n3->printInfo();
//---------------------测试代码结束-----------------------------

        server->do_accept();


        io_context.run();

    } catch (domain_error e) {
        cerr << e.what() << endl;
    }
    return 0;
}
