//
// Created by flo on 18/11/17.
//

#ifndef CPP_SPIDER_ICLIENT_HPP
#define CPP_SPIDER_ICLIENT_HPP

#include <boost/asio/ip/tcp.hpp>

class IClient {
public:
    IClient() = default;;
    ~IClient() = default;;
    virtual void start() = 0;
    virtual boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::lowest_layer_type& socket() = 0;
    virtual void handle_write(const boost::system::error_code& error) = 0;
    virtual void handle_read(const boost::system::error_code& error) = 0;
    virtual void disconnected() = 0;
};

#endif //CPP_SPIDER_ICLIENT_HPP
