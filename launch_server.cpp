#include <iostream>

#include "AppConstants.hpp"
#include "back/Server.hpp"

int main(int argc, char* argv[]) {
  // if (argc < 2) {
  //   std::cout << "port is not provided";
  //   return 0;
  // }
  // int port_of_the_server = atoi(argv[1]);
  int port_of_the_server = port;
  try {
    Server server("127.0.0.1", port_of_the_server);
    server.StartServer();
  } catch (const std::exception& except) {
    std::cout << except.what();
  }
}