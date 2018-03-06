#include "Client.hpp"
#include "INetwork.hpp"

class Server : public INetwork
{
public:
    Server(boost::asio::io_service &io_service, unsigned short port);
private:
    void start_accept() override;
    void handle_accept(IClient* new_client, const boost::system::error_code& error) override;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::vector<boost::asio::ip::tcp::socket *> socketV;
    void speak_to_client() override;
};