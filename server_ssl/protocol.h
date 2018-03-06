//
// Created by red on 10/4/17.
//

#ifndef CPP_SPIDER_PROTOCOL_H
#define CPP_SPIDER_PROTOCOL_H

#include <boost/array.hpp>

#define READSIZE 2048
#define WRITESIZE 2048

typedef struct  s_server
{
    boost::array<char, WRITESIZE>    buf;
}               t_server;

typedef struct  s_client
{
    boost::array<char, READSIZE>    buf;
}               t_client;

typedef enum    s_msg
{
    WELCOME,
    OK,
    DISCONNECT
}               t_msg;

#endif //CPP_SPIDER_PROTOCOL_H
