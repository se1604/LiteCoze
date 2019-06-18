#include <iostream>
#include <thread>
#include "netizen.h"
#include "privatechat.h"
#include "manager.h"
#include "dbbroker.h"

using namespace std;
using boost::asio::ip::tcp;
boost::asio::io_context io_context;

int main()
{
    try {
        tcp::endpoint endpoint(tcp::v6(), std::atoi("8080"));
        PrivateChat* privateChat = new PrivateChat(io_context, endpoint);

        DBBroker::getInstance()->initAccount();
        privateChat->accept();

        io_context.run();
    } catch (domain_error e) {
        cerr << e.what() << endl;
    }
    return 0;
}
