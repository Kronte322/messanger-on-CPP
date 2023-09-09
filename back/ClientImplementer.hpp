#pragma once
#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>

#include "../back/ClientStorage.hpp"

class ClientImplementer {
 public:
  ClientImplementer();
  int Implement(const std::string& message, ClientStorage& data);

 private:
  static int ImplementSignUp(std::string message, ClientStorage& data);

  static int ImplementLogIn(std::string message, ClientStorage& data);

  static int ImplementQuit(std::string message, ClientStorage& data);

  static int ImplementGetUserId(std::string message, ClientStorage& data);

  static int ImplementSendMessage(std::string message, ClientStorage& data);

  static int ImplementGetMessages(std::string message, ClientStorage& data);

  std::unordered_map<int, std::function<int(std::string, ClientStorage&)>>
      actions_;
};