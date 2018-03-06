//
// Created by Nagamo_s on 03/10/2017.
//

#ifndef UNTITLED2_LOCAL_HPP
#define UNTITLED2_LOCAL_HPP

#include <fstream>
#include "IEvent.hpp"
#include "GetEvent.hpp"
#include "Tools.hpp"

class Local
{
public:
    Local();
    ~Local();
    void KeyLogger();

private:
    IEvent *event;
};

#endif //UNTITLED2_LOCAL_HPP
