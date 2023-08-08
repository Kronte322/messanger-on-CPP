#include <string>
#include <vector>
#pragma once

class ClientStorage {
 public:
  int& SetUserId();
  int& SetReceiverId();
  std::vector<std::string>& SetMessages();

 private:
  int user_id_;
  int receiver_id_;
  std::vector<std::string> messages_;
};