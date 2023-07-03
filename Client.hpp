
#include <netinet/in.h>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>

#include "Message.hpp"

class Client {
 public:
  Client(const std::string& ip_address, int port);

  ~Client();

  void Connect();

  void ProcessConnection();

  auto& SetMutex();

  auto& SetConditionVariable();

  auto* SetMessage();

 private:
  Message* message_;
  std::mutex mutex_;
  std::condition_variable cond_variable_;
  sockaddr_in server_address_;
  sockaddr_in client_address_;
  std::string ip_address_of_the_server_;
  int port_ = 0;
  std::shared_ptr<int> client_discriptor_;
};