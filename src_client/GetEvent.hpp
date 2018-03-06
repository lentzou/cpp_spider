//
// Created by Nagamo_s on 15/11/2017.
//

#ifndef CPP_SPIDER_GETEVENT_HPP
#define CPP_SPIDER_GETEVENT_HPP

#include <fstream>
#include <String>
#include "IEvent.hpp"
#include "Data.hpp"
#include "Tools.hpp"

class GetEvent : public IEvent
{
public:
    GetEvent();
    virtual ~GetEvent();
    void Loop();
    virtual void InitLogger();
};

#endif //CPP_SPIDER_GETEVENT_HPP
