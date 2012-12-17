#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "snmptrap.h"


using boost::asio::ip::tcp;

class session
{
public:
  session(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&session::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

private:
  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
      boost::asio::buffer(data_, bytes_transferred);
      std::cout << data_ << std::endl;
      trap trap(data_);
    }
    else
    {
      delete this;
    }
  }

  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
          boost::bind(&session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }

  tcp::socket socket_;
  enum { max_length = 160 };
  char data_[max_length];
};

class server
{
public:
  server(boost::asio::io_service& io_service, short port)
    : io_service_(io_service),
      acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
  {
    start_accept();
  }

private:
  void start_accept()
  {
    session* new_session = new session(io_service_);
    acceptor_.async_accept(new_session->socket(),
      boost::bind(&server::handle_accept, this, new_session,
        boost::asio::placeholders::error));
  }

  void handle_accept(session* new_session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_session->start();
    }
    else
    {
      delete new_session;
    }

    start_accept();
  }

  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
};

void handler( const boost::system::error_code& error, int signal_number)
{
  if (!error)
  {
    // A signal occurred.
    std::cout << "Signal Received" << std::endl;
    exit(0); 
  }
}

int main(int argc, char* argv[])
{
  int myError = 1;
  while(myError) {
    try
    {
      if (argc != 2)
      {
        std::cerr << "Usage: async_tcp_echo_server <port>\n";
        return 1;
      }

      boost::asio::io_service io_service;
      // Construct a signal set registered for process termination.
      boost::asio::signal_set signals(io_service, SIGINT, SIGTERM);
      // Start an asynchronous wait for one of the signals to occur.
      signals.async_wait(handler);

      using namespace std; // For atoi.
      server s(io_service, atoi(argv[1]));

      io_service.run();
    }
    catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << "\n";
    }
    myError = 0;
  }
  return 0;
}
