#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
//#include <boost/test/unit_test.hpp>

//#define BOOST_TEST_MODULE const_string test

using boost::asio::ip::tcp;

enum { max_length = 1024 };

char signature[] = "\x53\x4e\x4d\x50";
char length[] = "\xA4\x34\xA1\x32";
char event[] = "\x02\x01\x02\x02\x02\x03\xe8 \
                \x16\x06\x0b\x4c\x45\x4e\x58";

class msg {
  public:
    msg();
    msg(char* buff){
      unpack(buff);
      std::cout << "successful\n";
      std::cout.write(length,4);
    };
  private:
    int pack();
    int unpack(char* buff){
      printf("%s\n",buff);
      return 1;
    };
};
class pdu {
  public:
    pdu();
    int send();
    int close();

  private:
    int pack();
    int unpack();
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);
    tcp::resolver::iterator iterator = resolver.resolve(query);

    tcp::socket s(io_service);
    boost::asio::connect(s, iterator);

    using namespace std; // For strlen.
    cout << "Enter message: ";
    char request[max_length];
    std::cin.getline(request, max_length);
    size_t request_length = strlen(request);
    boost::asio::write(s, boost::asio::buffer(request, request_length));

    char reply[max_length];
    size_t reply_length = boost::asio::read(s,
        boost::asio::buffer(reply, request_length));
    std::cout << "Reply is: ";
    std::cout.write(reply, reply_length);
    std::cout << "\n";
    msg msg(reply);
/*
    if(msg tcp_msg(reply)){
      exit(1);
    };
*/
  }
  catch (std::exception& e)
  {
//    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
