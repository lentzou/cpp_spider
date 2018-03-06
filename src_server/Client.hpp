//
// client.hpp for client in /home/florian.lentz/tek3/cpp_spider/src_server
//
// Made by florian lentz
// Login   <florian.lentz@epitech.net>
//
// Started on  Sun Oct  8 22:32:28 2017 florian lentz
// Last update Sun Oct  8 22:34:27 2017 florian lentz
//

#include <thread>
#include <fstream>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "CoreGraph.hpp"
#include "IClient.hpp"
#include "protocol.h"

class Client : public IClient
{
public:
    Client(boost::asio::io_service& io_service)
            : socket_(io_service)
    {
    }
    boost::asio::ip::tcp::socket& socket() override {
        return socket_;
    }
private:
    void start() override;
    void disconnected(boost::asio::ip::tcp::socket& socket_) override;
    void handle_read(const boost::system::error_code& error) override;
    void handle_write(const boost::system::error_code& error) override;
    void close();
    t_client client;
    t_server server;
    std::ofstream _file;
    std::string ClientIp_;
    boost::asio::ip::tcp::socket socket_;
};