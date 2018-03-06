#pragma once

#ifndef INETWORK_HPP
#define INETWORK_HPP

class INetwork {
public:
	virtual ~INetwork() {}
	virtual void tryConnection() = 0;
	virtual void handle_read() = 0;
	virtual void handle_write() = 0;

};

#endif