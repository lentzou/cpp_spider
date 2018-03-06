//
// Created by Nagamo_s on 15/11/2017.
//

#ifndef CPP_SPIDER_IEVENT_HPP
#define CPP_SPIDER_IEVENT_HPP


#include <fstream>

class IEvent {
public :
	virtual ~IEvent() {}
    virtual void InitLogger() = 0;
};

#endif //CPP_SPIDER_IEVENT_HPP
