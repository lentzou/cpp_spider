//
// Created by florian.lentz on 10/7/17.
//

#include "Client.hpp"

void Client::start()
{
    ClientIp_ = socket_.lowest_layer().remote_endpoint().address().to_string();
    std::cout << "Client " << ClientIp_ << " connected" << std::endl;
    m.lock();
    //files.push(ClientIp_);
    m.unlock();
    _file.open(ClientIp_.c_str(), std::ofstream::app);
    std::time_t time = std::time(nullptr);
    _file << std::asctime(std::localtime(&time)) << "Connection client" << std::endl;
    _file.close();
    socket_.async_handshake(boost::asio::ssl::stream_base::server,
                            boost::bind(&Client::handle_start, this, boost::asio::placeholders::error));
}

void Client::handle_start(const boost::system::error_code& error)
{
  std::fill_n(server.buf.begin(), WRITESIZE, 0);
  std::fill_n(client.buf.begin(), READSIZE, 0);
    send_byte(WELCOME);
    boost::asio::async_write(socket_, boost::asio::buffer(&server, sizeof(server)), boost::bind(&Client::handle_read, this, boost::asio::placeholders::error));
}

void Client::send_byte(t_msg msg)
{
    if (msg == WELCOME)
        server.buf[0] = '1';
    else if (msg == OK)
        server.buf[0] = '2';
    else
        server.buf[0] = '3';
    server.buf[1] = '\n';
}

void Client::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
        if (client.buf[0] == '\n')
            std::fill_n(server.buf.begin(), WRITESIZE, 0);
        else
            send_byte(OK);
        boost::asio::async_write(socket_, boost::asio::buffer(&server, sizeof(server)), boost::bind(&Client::handle_read, this, boost::asio::placeholders::error));
    }
    else
        disconnected();
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
            std::cout << ClientIp_ << ": has sent a message" << std::endl;
        }
        std::fill_n(client.buf.begin(), READSIZE, 0);
    }
    else
        disconnected();
}

void Client::disconnected()
{
    send_byte(DISCONNECT);
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
    socket_.lowest_layer().close();
}
