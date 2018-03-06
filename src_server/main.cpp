#include "Server.hpp"

 void			graphMode()
 {
    try
    {
        CoreGraph		core;

        core.startGraphMode();
    }
    catch (const char *s)
    {
        std::cout << s << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "An error occured: " << e.what() << std::endl;
    }
    catch ( ... )
    {
        std::cout << "Undefined error" << std::endl;
    }
 }

int main(int ac, char* av[])
{
    try
    {
        std::thread t(graphMode);
        boost::asio::io_service io_service;
        INetwork *network = new Server(io_service, av[1] != NULL ? std::atoi(av[1]) : 4242);
        std::thread rd([network]() { network->speak_to_client() ;});
        network->start_accept();
        io_service.run();
        stop = true;
	    t.join();
        rd.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return (0);
}
