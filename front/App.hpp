#pragma once

#include "../back/Client.hpp"
#include "../back/ClientController.hpp"
#include "../back/ClientImplementer.hpp"
#include "../back/ClientStorage.hpp"
#include "../front/UI.hpp"

class App {
 public:
  App();
  ~App();

 private:
  void ProcessMainLoop();
  DefaultClient client_;
  ClientImplementer implementer_;
  ClientController client_controller_;
  ClientStorage data_;
  UI ui_;
};
