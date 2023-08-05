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
  static int ImplementSignUp(const std::string& message, ClientStorage& data);

  static int ImplementLogIn(const std::string& message, ClientStorage& data);

  static int ImplementQuit(const std::string& message, ClientStorage& data);

  std::unordered_map<int,
                     std::function<int(const std::string&, ClientStorage&)>>
      actions_;
};