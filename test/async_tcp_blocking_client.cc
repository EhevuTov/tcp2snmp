#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/algorithm/string.hpp>

using boost::asio::ip::tcp;

enum { max_length = 160 };

struct data {
  char signature[6];
  char eventType[2];
  char teknoID[6];
  char linkSet[18];
  char linkQual[56];
  char origin[18];
  char destin[18];
  char threshold[4];
  char occupancy[4];
  char direction[1];
  char padding[27];
};

typedef struct data Data;
unsigned char* buffer[160];

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

    using namespace std;

    Data* request;
    request=(Data*)malloc(sizeof(Data));
    memset(request, '\0', sizeof(Data));
    if (NULL == request) {return 0;};

    strcpy(request->signature, "SNMP");
    strcpy(request->eventType, "1");
    strcpy(request->teknoID, "1000");
    strcpy(request->linkSet, "LS0001");
    strcpy(request->linkQual, "6");
    strcpy(request->origin, "LENXPA671AD");
    strcpy(request->destin, "LENXPA782BF");
    strcpy(request->threshold, "60");
    strcpy(request->occupancy, "70");
    strcpy(request->direction, "1");

    size_t request_length = sizeof(Data);

    boost::asio::write(s, boost::asio::buffer((void*)request, request_length));

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
