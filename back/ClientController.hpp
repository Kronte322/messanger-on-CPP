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

  int SendGetUserIdMessage(const std::string& user_name);

  int SendTextMessage(int sender_id, int receiver_id,
                      const std::string& message);

 private:
  DefaultClient& client_;
  ClientStorage& data_;
  ClientImplementer& implementer_;
};