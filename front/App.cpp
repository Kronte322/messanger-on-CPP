#include "./App.hpp"

#include <iostream>

#include "../AppConstants.hpp"

App::App()
    : client_controller_(client_, data_, implementer_),
      ui_(client_controller_, data_) {
  try {
    client_.Connect("127.0.0.1", port);
  } catch (const std::exception& except) {
    std::cout << except.what();
    throw;
  }
  ProcessMainLoop();
}

App::~App() = default;

void App::ProcessMainLoop() { ui_.RunGUI(); }
