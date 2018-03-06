//
// Created by Nagamo_s on 04/10/2017.
//

#include "Data.hpp"

Data::Data() : file("log", std::ios::app), tools(Tools::Instance())
{
    file.close();
    localtime_s(&buf, &t);
    t = time(NULL);
}

Data::~Data()
{
}

const HHOOK &Data::getKeyBoardHook()
{
    return (hKeyboardHook);
}

const HHOOK &Data::getMouseHook()
{
    return (hMouseHook);
}

const int &Data::getX()
{
    return (x);
}

const int &Data::getY()
{
    return (y);
}

const time_t &Data::getTime()
{
    return (t);
}

void Data::setKeyBoardHook(const HHOOK &keyborad)
{
 hKeyboardHook = keyborad;
}

void Data::setMouseHook(const HHOOK &mouse)
{
    hMouseHook = mouse;
}

void Data::setX(const int &X)
{
    x = X;
}

void Data::setY(const int &Y)
{
    y = Y;
}

void Data::setTime(const time_t &time)
{
    t = time;
}