#include "Client.hpp"

#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>

#include <iostream>

#include "../front/App.hpp"
#include "Message.hpp"

Client::Client(const std::string& ip_address, int port, App& app)
    : ip_address_of_the_server_(ip_address), port_(port), app_(app) {
  bzero((char*)&server_address_, sizeof(server_address_));
  bzero((char*)&client_address_, sizeof(client_address_));

  server_address_.sin_family = AF_INET;
  server_address_.sin_port = htons(port_);
  inet_pton(AF_INET, ip_address_of_the_server_.c_str(),
            &server_address_.sin_addr);

  auto deleter = [](int* socket) { close(*socket); };

  client_discriptor_ =
      std::shared_ptr<int>(new int(socket(AF_INET, SOCK_STREAM, 0)), deleter);

  if (*client_discriptor_ < 0) {
    throw std::runtime_error("error on creating socket\n");
  }
}

Client::~Client() = default;

void Client::Connect() {
  if (connect(*client_discriptor_, (struct sockaddr*)&server_address_,
              sizeof(server_address_)) < 0) {
    throw std::runtime_error("connection failled");
  }

  std::cout << "Client starting...\n";
}

void Client::ProcessConnection() {
  char message[256];
  std::string buf;
  while (strcmp(message, "quit") != 0) {
    bzero(&message, sizeof(message));
    std::unique_lock lock(mutex_);
    cond_variable_.wait(lock);
    buf = message_->Serialization();

    if (write(*client_discriptor_, buf.c_str(), buf.size()) < 0) {
      throw std::runtime_error("error while writing to socket folder");
    }
    if (read(*client_discriptor_, message, sizeof(message)) < 0) {
      throw std::runtime_error("error while reading from socket folder");
    }
    try {
      static_cast<ServerMessage*>(BaseMessage::Deserialization(message).get())
          ->Implement(*this);
    } catch (const std::exception& except) {
      std::cout << except.what();
    }
  }
}

std::mutex& Client::SetMutex() { return mutex_; }

std::condition_variable& Client::SetConditionVariable() {
  return cond_variable_;
}

std::unique_ptr<ClientMessage>& Client::SetMessage() { return message_; }

App& Client::SetApp() { return app_; }