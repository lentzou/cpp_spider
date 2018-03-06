//
// Created by flo on 18/11/17.
//

#ifndef CPP_SPIDER_ICLIENT_HPP
#define CPP_SPIDER_ICLIENT_HPP

class IClient {
public:
    IClient() = default;;
    ~IClient() = default;;
    virtual void start() = 0;
    virtual boost::asio::ip::tcp::socket& socket() = 0;
    virtual void handle_write(const boost::system::error_code& error) = 0;
    virtual void handle_read(const boost::system::error_code& error) = 0;
    virtual void disconnected(boost::asio::ip::tcp::socket& socket_) = 0;
};

#endif //CPP_SPIDER_ICLIENT_HPP
