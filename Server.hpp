#pragma once

#include <netinet/in.h>

#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "DBConnection.hpp"

class Server {
 public:
  Server(const std::string& ip_address, int port);

  ~Server();

  void StartServer();

  static void DisconnectMessage(const sockaddr_in& address);

  void ProcessConnection(int client_discriptor, sockaddr_in client_address);

  const DBConnection& GetDbConnection();

  std::vector<std::string>& SetMessages();

 private:
  std::mutex mutex_;
  DBConnection db_connection_;
  struct sockaddr_in server_address_;
  struct sockaddr_in client_address_;
  std::string ip_address_;
  int port_ = 0;
  std::vector<std::thread> threads_;
  std::shared_ptr<int> socket_discriptor_;
  std::vector<std::string> messages_;
};
