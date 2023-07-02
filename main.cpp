#include <iostream>

#include "Client.hpp"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "port is not provided";
    return 0;
  }
  int port_of_the_server = atoi(argv[1]);
  try {
    Client client("127.0.0.1", port_of_the_server);
    client.Connect();
    client.ProcessConnection();
  } catch (const std::string& str) {
    std::cout << str;
  }
}