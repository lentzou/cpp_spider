#ifndef _TOOLS_HPP_
# define _TOOLS_HPP_

#include <iostream>
#include <ctime>
#include "Singleton.hpp"


class Tools : public Singleton<Tools>
{
public:
	friend class Singleton<Tools>;
	Tools();
	~Tools() {}
	bool		connect;
	std::string input;
	void		setTime(const time_t &);
	time_t		t;
	tm			buf;
	bool		pause;
};
#endif
