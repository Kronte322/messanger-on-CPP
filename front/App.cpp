#include "./App.hpp"

#include <iostream>

App::App() {
  try {
    client_.Connect("127.0.0.1", 5555);
  } catch (const std::exception& except) {
    std::cout << except.what();
  }
  ProcessMainLoop();
}

App::~App() = default;

void App::ProcessMainLoop() { ui_.RunGUI(); }
