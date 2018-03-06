//
// Created by Nagamo_s on 04/10/2017.
//

#ifndef UNTITLED3_NETWORK_HPP
#define UNTITLED3_NETWORK_HPP

#include <array>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "protocol.h"
#include "Tools.hpp"
#include "INetwork.hpp"

class Network : public INetwork
{
public:
    Network(boost::asio::io_service& io_service, const std::string &, const std::string &);
    virtual ~Network();
	virtual void tryConnection();
	virtual void handle_read();
    virtual void handle_write();

private:	
	void checkTime();
	void readInput();
    void readFile();    
    void handleResolve(const boost::system::error_code& err, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
    void handleConnect(const boost::system::error_code& err);
    
    t_client client;
    t_server server;
    std::string ip;
    std::string port;
    std::ifstream _file;
	Tools &tools;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::resolver resolver_;

};


#endif //UNTITLED3_NETWORK_HPP
