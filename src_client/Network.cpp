//
// Created by Nagamo_s on 04/10/2017.
//

#include "Network.hpp"

Network::Network(boost::asio::io_service& io_service, const std::string &Ip, const std::string &Port)
: socket_(io_service), resolver_(io_service), ip(Ip), port(Port), tools(Tools::Instance())
{	
	tryConnection();	
}

Network::~Network()
{
}

void Network::handle_read()
{
	try
	{
		while (1)
		{
			if (tools.connect == false)
				return;
			if (socket_.is_open())
			{
				std::fill_n(server.buf.begin(), READSIZE, 0);
				socket_.read_some(boost::asio::buffer(&server, sizeof(server)));
				if (server.buf[0] != '\n' && server.buf[0] != 0)
				{
					if (!(strcmp(server.buf.data(), "pause")))
						tools.pause = true;
					if (!(strcmp(server.buf.data(), "start")))
						tools.pause = false;
					std::cout << server.buf.data();
				}
			}
			else
			{
				socket_.close();
				return;
			}
		}
	}
	catch (...) {
		socket_.close();
		return;
	}
}

void Network::handle_write()
{
	try
	{
		readFile();
		while (1)
		{
			if (tools.connect == false)
				return;
			if (socket_.is_open())
			{
				std::fill_n(client.buf.begin(), WRITESIZE, 0);
				if (!tools.pause)
					readInput();
			}
			else
			{
				socket_.close();
				return;
			}
		}
	}
	catch (...) {
		socket_.close();
		return;
	}
}

void Network::tryConnection()
{
	if (tools.input != "")
	{
		std::ofstream file;
		file.open("log", std::ios::app);
		file << tools.input << std::endl;
		tools.input = "";
	}
	tools.connect = false;
	try {
		boost::asio::ip::tcp::resolver::query query(ip, port);
		resolver_.async_resolve(query, boost::bind(&Network::handleResolve, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::iterator));

	}
	catch (...) {
		socket_.close();
		tryConnection();
	}
}
void Network::handleResolve(const boost::system::error_code& err,
                    boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	try {
		if (!err)
		{
			boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
			socket_.async_connect(endpoint,
				boost::bind(&Network::handleConnect, this,
					boost::asio::placeholders::error));
		}
		else
		{
			socket_.close();
			tryConnection();
		}
	}
	catch (...) {
		socket_.close();
		tryConnection();
	}
}

void Network::handleConnect(const boost::system::error_code& err)
{
	try
	{
		if (!err)
		{
			tools.connect = true;
			std::thread t1([this]() { this->handle_read(); });
			std::thread t2([this]() { this->handle_write(); });
			t1.join();
			t2.join();
			socket_.close();
			tryConnection();
		}
		else
		{
			socket_.close();
			tryConnection();
		}
	}
	catch (...) {
		socket_.close();
		tryConnection();
	}
}

void Network::checkTime()
{
	tm tmp;

	tools.t = time(nullptr);
	localtime_s(&tmp, &tools.t);
	if (tmp.tm_mday == tools.buf.tm_mday && tmp.tm_mon == tools.buf.tm_mon &&
		tmp.tm_year == tools.buf.tm_year && tmp.tm_hour == tools.buf.tm_hour &&
		tmp.tm_min == tools.buf.tm_min && tmp.tm_sec == tools.buf.tm_sec)
		return;
	tools.buf = tmp;
	
	if (tools.input != "")
		tools.input += "\n";
}

void Network::readInput() 
{
	int i = 0;
	char c;
	checkTime();
	if (tools.input != "")
	{
		std::string line;
		if (tools.input.find("\n") == std::string::npos)
			return;
		line = tools.input.substr(0, tools.input.find("\n") + 1);
		if (line != "")
		{
			while (line[i] != '\0')
			{
				c = line[i];
				client.buf[i] = c;
				i++;
			}
			socket_.write_some(boost::asio::buffer(&client, sizeof(client)));
			tools.input.erase(0, tools.input.find("\n") + 1);
		}
	}
}

void Network::readFile() {
    std::string line;
    int i = 0;
    _file.open("log");
    if (_file.is_open()) {
		while (getline(_file, line))
		{
			if (line != "")
			{
				std::fill_n(client.buf.begin(), WRITESIZE, 0);
				i = 0;
				while (i != line.size())
				{
					client.buf[i] = line.c_str()[i];
					i++;
				}
				client.buf[i] = '\n';
				socket_.write_some(boost::asio::buffer(&client, sizeof(client)));
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}		
		_file.close();
		remove("log");
    }
}