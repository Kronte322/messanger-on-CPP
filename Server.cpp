#include "Server.hpp"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <csignal>
#include <exception>
#include <iostream>
#include <iterator>
#include <pqxx/pqxx>

#include "Message.hpp"

Server::Server(const std::string& ip_address, int port)
    : ip_address_(ip_address), port_(port) {
  bzero((char*)&server_address_, sizeof(server_address_));
  bzero((char*)&client_address_, sizeof(client_address_));

  server_address_.sin_family = AF_INET;
  server_address_.sin_port = htons(port_);
  inet_pton(AF_INET, ip_address_.c_str(), &server_address_.sin_addr);

  auto deleter = [](int* socket) {
    close(*socket);
    delete socket;
  };

  socket_discriptor_ =
      std::shared_ptr<int>(new int(socket(AF_INET, SOCK_STREAM, 0)), deleter);

  if (*socket_discriptor_ < 0) {
    throw std::runtime_error("error on creating socket\n");
  }

  if (bind(*socket_discriptor_, (struct sockaddr*)&server_address_,
           sizeof(server_address_)) < 0) {
    throw std::runtime_error("error on creating socket\n");
  }
}

Server::~Server() = default;

void Server::StartServer() {
  signal(SIGPIPE, SIG_IGN);
  if (listen(*socket_discriptor_, 5) < 0) {
    throw std::runtime_error("error listen\n");
  }

  int client_discriptor = 0;
  socklen_t client_len = sizeof(client_address_);
  std::cout << "Server starting...\n";

  while (true) {
    client_discriptor = accept(*socket_discriptor_,
                               (struct sockaddr*)&client_address_, &client_len);
    std::cout << "server: got connection from "
              << std::string(inet_ntoa(client_address_.sin_addr))
              << " port: " << ntohs(client_address_.sin_port) << std::endl;
    if (client_discriptor < 0) {
      std::cout << "no acceptions";
    } else {
      threads_.emplace_back(&Server::ProcessConnection, this, client_discriptor,
                            client_address_);
      threads_[threads_.size() - 1].detach();
    }
  }
}

void Server::DisconnectMessage(const sockaddr_in& address) {
  std::cout << "Disconnected: " << std::string(inet_ntoa(address.sin_addr))
            << " port: " << ntohs(address.sin_port) << std::endl;
}

void Server::ProcessConnection(int client_discriptor,
                               sockaddr_in client_address) {
  char buffer[256];
  char message[] = "correct";
  while (strcmp(buffer, "quit") != 0) {
    bzero(&buffer, sizeof(buffer));
    if (write(client_discriptor, message, sizeof(message)) < 0) {
      std::cout << "cannot write from socket" << std::endl;
      DisconnectMessage(client_address);
      break;
    }
    if (read(client_discriptor, buffer, 255) < 0) {
      std::cout << "cannot read from socket" << std::endl;
      DisconnectMessage(client_address);
      break;
    }
    {
      std::lock_guard<std::mutex> guard(mutex_);
      messages_.push_back(buffer);
      std::copy(messages_.begin(), messages_.end(),
                std::ostream_iterator<std::string>(std::cout, " "));
      std::cout << std::endl;
    }
  }
}

const DBConnection& Server::GetDbConnection() { return db_connection_; }
