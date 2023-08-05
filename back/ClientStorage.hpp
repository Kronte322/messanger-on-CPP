#include <vector>
#pragma once

class ClientStorage {
 public:
  int& SetUserId();

 private:
  int user_id_;
};