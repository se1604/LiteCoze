#include <iostream>
#include <thread>
#include "netizen.h"
#include "privatechat.h"
#include "manager.h"

using namespace std;
using boost::asio::ip::tcp;
boost::asio::io_context io_context;

int main()
{
    try {

        tcp::endpoint endpoint(tcp::v6(), std::atoi("8080"));
        PrivateChat* privateChat = new PrivateChat(io_context, endpoint);

        auto n1 = new Netizen{111, "111", "Tom"};
        auto n2 = new Netizen{222, "222", "Lily"};
        auto n3 = new Netizen{333, "333", "Amy"};
        auto n4 = new Netizen{444, "444", "Bob"};
        Manager::getInstance()->printInfo();
        n1->addFriend(n2, 111222);
        n1->addFriend(n3, 111333);

        privateChat->accept();

        io_context.run();
    } catch (domain_error e) {
        cerr << e.what() << endl;
    }
    return 0;
}
