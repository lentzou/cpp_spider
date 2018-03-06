//
// Created by flo on 18/11/17.
//

#ifndef CPP_SPIDER_INETWORK_HPP
#define CPP_SPIDER_INETWORK_HPP

class INetwork {
public:
    INetwork() = default;;
    ~INetwork() = default;;
    virtual void start_accept() = 0;
    virtual void handle_accept(IClient* new_client, const boost::system::error_code& error) = 0;
    virtual void speak_to_client() = 0;
};

#endif //CPP_SPIDER_INETWORK_HPP
