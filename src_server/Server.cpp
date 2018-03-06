#include "Server.hpp"

void Server::speak_to_client()
{
	std::string buf;
	t_server server;

	while (1)
	{
		std::fill_n(server.buf.begin(), READSIZE, 0);
		getline(std::cin, buf);
		for (unsigned int i = 0; i < buf.size(); i++)
			server.buf[i] = buf[i];
		for (unsigned int i = 0; i < socketV.size(); i++)
		{
			if (socketV[i]->is_open())
			{
				try
				{
					if ((socketV[i]->write_some(boost::asio::buffer(&server, sizeof(server)))) == 0)
					{
						socketV[i]->close();
						socketV.erase(socketV.begin() + i);
					}
				}
				catch (const std::exception& e)
				{
				}
			}
		}
	}
}

Server::Server(boost::asio::io_service& io_service, unsigned short port)
        : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    std::cout << "Server started with port : " << port << std::endl;
}

void Server::start_accept()
{
    IClient* new_client = new Client(acceptor_.get_io_service());
    acceptor_.async_accept(new_client->socket(), boost::bind(&Server::handle_accept, this, new_client, boost::asio::placeholders::error));
}

void Server::handle_accept(IClient* new_client, const boost::system::error_code& error)
{
    if (!error) 
	{
		socketV.push_back(&new_client->socket());
        new_client->start();
    }
    else
        delete new_client;
    start_accept();
}
