#pragma once
#include "../back/Client.hpp"
#include "../back/ClientImplementer.hpp"
#include "../back/ClientStorage.hpp"

class ClientController {
 public:
  ClientController(DefaultClient& client, ClientStorage& data,
                   ClientImplementer& implementer);

  int SendSignUpMessage(const std::string& user_name,
                        const std::string& password);

  int SendLogInMessage(const std::string& user_name,
                       const std::string& password);

 private:
  DefaultClient& client_;
  ClientStorage& data_;
  ClientImplementer& implementer_;
};