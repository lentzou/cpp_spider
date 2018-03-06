//
// client.cpp for cpp_spider in /home/florian.lentz/tek3/cpp_spider/src_server
//
// Made by florian lentz
// Login   <florian.lentz@epitech.net>
//
// Started on  Sun Oct  8 22:33:07 2017 florian lentz
// Last update Sun Oct  8 22:36:16 2017 florian lentz
//

#include "Client.hpp"

void Client::start()
{
    ClientIp_ = socket_.remote_endpoint().address().to_string();
    std::cout << "Client " << ClientIp_ << " connected" << std::endl;
   m.lock();
   files.push(ClientIp_);
   m.unlock();
   _file.open(ClientIp_.c_str(), std::ofstream::app);
   std::time_t time = std::time(nullptr);
   _file << std::asctime(std::localtime(&time)) << "Connection client" << std::endl;
   _file.close();
   std::fill_n(server.buf.begin(), WRITESIZE, 0);
   std::fill_n(client.buf.begin(), READSIZE, 0);
   boost::asio::async_write(socket_, boost::asio::buffer(&server, sizeof(server)), boost::bind(&Client::handle_read, this, boost::asio::placeholders::error));
}

void Client::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
        if (client.buf[0] == '\n')
            std::fill_n(server.buf.begin(), WRITESIZE, 0);
        boost::asio::async_write(socket_, boost::asio::buffer(&server, sizeof(server)), boost::bind(&Client::handle_read, this, boost::asio::placeholders::error));
    }
    else
        disconnected(socket_);
}

void Client::handle_read(const boost::system::error_code& error)
{
    if (!error)
    {
        socket_.async_read_some(boost::asio::buffer(&client, sizeof(client)), boost::bind(&Client::handle_write, this, boost::asio::placeholders::error));
        if (client.buf[0] != '\n' && client.buf[0] != 0)
        {
            _file.open(ClientIp_.c_str(), std::ofstream::app);
            std::time_t time = std::time(nullptr);
            _file << std::asctime(std::localtime(&time));
            _file << client.buf.data();
            _file.close();
			std::cout << ClientIp_ << ": " << client.buf.data();
		}
        std::fill_n(client.buf.begin(), READSIZE, 0);
    }
    else
        disconnected(socket_);
}

void Client::disconnected(boost::asio::ip::tcp::socket& socket_)
{

    _file.open(ClientIp_.c_str(), std::ofstream::app);
    std::time_t time = std::time(nullptr);
    _file << std::asctime(std::localtime(&time)) << "Disconnection client" << std::endl;
    _file.close();
    std::cout << "Client " << ClientIp_ << " disconnected" << std::endl;
    close();
    delete this;
}

void Client::close()
{
    socket_.close();
}
