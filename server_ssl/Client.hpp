//
// Created by florian.lentz on 10/7/17.
//

#ifndef CPP_SPIDER_CLIENT_HPP
#define CPP_SPIDER_CLIENT_HPP

#include <thread>
#include <fstream>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "protocol.h"
#include "CoreGraph.hpp"
#include "IClient.hpp"

class Client : public IClient
{
public:
    Client(boost::asio::io_service& io_service, boost::asio::ssl::context& context)
            : socket_(io_service, context)
    {
    }
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::lowest_layer_type& socket() override
    {
        return socket_.lowest_layer();
    }
    void start() override;
    void disconnected() override;
    void handle_read(const boost::system::error_code& error) override;
    void handle_write(const boost::system::error_code& error) override;
private:
    void close();
    void send_byte(t_msg msg);
    void handle_start(const boost::system::error_code& error);
    t_client client;
    t_server server;
  //  std::ofstream _file;
    std::string ClientIp_;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
};

#endif //CPP_SPIDER_CLIENT_HPP
