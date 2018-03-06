//
// Created by Nagamo_s on 03/10/2017.
//

#ifndef UNTITLED2_CORE_HPP
#define UNTITLED2_CORE_HPP

#include <thread>
#include <iostream>
#include <ctime>
#include <fstream>
#include <boost/asio.hpp>
#include "Tools.hpp"
#include "Local.hpp"
#include "Network.hpp"

class Core
{
public:
    Core();
    ~Core();
    void   client();
    boost::asio::io_service io_service;
	Local	*local;
	INetwork *network; 
	
};


#endif //UNTITLED2_CORE_HPP
