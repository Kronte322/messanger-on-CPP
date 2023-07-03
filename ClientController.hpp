#pragma once

#include <iostream>

#include "Client.hpp"

class ClientController {
 public:
  void SendMessage(const Message& message);

 private:
  Client& client_;
};