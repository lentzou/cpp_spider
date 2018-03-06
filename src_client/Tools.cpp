#include "Tools.hpp"

Tools::Tools()
{
	connect = false;
	pause = false;
	input = "";
	localtime_s(&buf, &t);
	t = time(NULL);
}

void Tools::setTime(const time_t &time)
{
	t = time;
}