#ifndef CPP_SPIDER_SERVER_HPP
#define CPP_SPIDER_SERVER_HPP

#include "Client.hpp"
#include "INetwork.hpp"

class Server : public INetwork
{
public:
    Server(boost::asio::io_service& io_service, unsigned short port)
            : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), _context(io_service, boost::asio::ssl::context::sslv23)
    {
        try
        {
            _context.set_options(boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2 |
                                 boost::asio::ssl::context::single_dh_use);
            _context.use_certificate_chain_file("../ssl/server.crt");
            _context.use_private_key_file("../ssl/server.key", boost::asio::ssl::context::pem);
            _context.use_tmp_dh_file("../ssl/dh1024.pem");
        }
        catch (std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
            return ;
        }
        std::cout << "Server started with port : " << port << std::endl;
    }
    void start_accept() override;
    void handle_accept(IClient* new_client, const boost::system::error_code& error) override;
private:
    boost::asio::ssl::context _context;
    boost::asio::ip::tcp::acceptor acceptor_;
};

#endif //CPP_SPIDER_SERVER_HPP
