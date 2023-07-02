
#include <netinet/in.h>

#include <memory>
#include <string>

class Client {
 public:
  Client(const std::string& ip_address, int port);

  ~Client();

  void Connect();

  void ProcessConnection();

 private:
  sockaddr_in server_address_;
  sockaddr_in client_address_;
  std::string ip_address_of_the_server_;
  int port_ = 0;
  std::shared_ptr<int> client_discriptor_;
};