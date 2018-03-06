#include "Server.hpp"

void Server::start_accept()
{
    IClient *new_client = new Client(acceptor_.get_io_service(), _context);
    acceptor_.async_accept(new_client->socket(),
                           boost::bind(&Server::handle_accept, this, new_client, boost::asio::placeholders::error));
}

void Server::handle_accept(IClient* new_client, const boost::system::error_code& error)
{
    if (!error)
        new_client->start();
    else
        delete new_client;
    start_accept();
}
