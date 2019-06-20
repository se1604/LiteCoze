#include <iostream>
#include <thread>
#include "netizen.h"
#include "server.h"
#include "accountmanager.h"
#include "dbbroker.h"
#include "privatechat.h"

using namespace std;
using boost::asio::ip::tcp;
boost::asio::io_context io_context;

int main()
{
    try {

        tcp::endpoint endpoint(tcp::v6(), std::atoi("8080"));
        Server* server = new Server(io_context, endpoint);

        DBBroker::getInstance()->initAccount();
        auto privateChat = new PrivateChat();
        privateChat->initFriend();
        privateChat->initGroup();
        DBBroker::getInstance()->addGroupTODB(100000001,"软件工程专业群",333);
       // server->accept();

        io_context.run();
    } catch (domain_error e) {
        cerr << e.what() << endl;
    }
    return 0;
}
