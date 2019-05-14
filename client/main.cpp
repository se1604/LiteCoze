#include<boost/asio/io_service.hpp>
#include<boost/asio/ip/tcp.hpp>
#include<boost/bind.hpp>
#include<boost/shared_ptr.hpp>
#include<boost/enable_shared_from_this.hpp>
#include<string>
#include<iostream>
#include<boost/asio/streambuf.hpp>
#include<boost/asio/placeholders.hpp>
#include<boost/asio.hpp>


/*typedef boost::shared_ptr<client> client_ptr;

int main()
{
    boost::asio::io_service io_service;
    tcp::endpoint endpoint(address::from_string("127.0.0.1"), 1000);

    client_ptr new_session(new client(io_service, endpoint));
    new_session->start();
    io_service.run();
    std::string ss;
    std::cin >> ss;
    return 0;
}*/
