#include "./App.hpp"

#include <iostream>

App::App()
    : client_controller_(client_, data_, implementer_),
      ui_(client_controller_) {
  try {
    client_.Connect("127.0.0.1", 5555);
  } catch (const std::exception& except) {
    std::cout << except.what();
    throw;
  }
  ProcessMainLoop();
}

App::~App() = default;

void App::ProcessMainLoop() { ui_.RunGUI(); }
