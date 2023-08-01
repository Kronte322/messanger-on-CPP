#pragma once

#include "../back/Client.hpp"
#include "../back/ClientStorage.hpp"
#include "../front/UI.hpp"

class App {
 public:
  App();
  ~App();

 private:
  void ProcessMainLoop();

  ClientStorage data_;
  DefaultClient client_;
  UI ui_;
};
