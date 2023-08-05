#include "Client.hpp"

#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>

#include <csignal>
#include <iostream>

#include "../front/App.hpp"
#include "Message.hpp"

DefaultClient::DefaultClient() = default;

DefaultClient::~DefaultClient() { Disconnect(); }

void DefaultClient::Connect(const std::string& ip_address, int port) {
  bzero((char*)&server_address_, sizeof(server_address_));

  server_address_.sin_family = AF_INET;
  server_address_.sin_port = htons(port);
  inet_pton(AF_INET, ip_address.c_str(), &server_address_.sin_addr);

  auto deleter = [](int* socket) { close(*socket); };

  client_discriptor_ =
      std::shared_ptr<int>(new int(socket(AF_INET, SOCK_STREAM, 0)), deleter);

  if (*client_discriptor_ < 0) {
    throw std::runtime_error("error on creating socket\n");
  }

  if (connect(*client_discriptor_, (struct sockaddr*)&server_address_,
              sizeof(server_address_)) < 0) {
    throw std::runtime_error("connection failled");
  }

  std::cout << "Client starting...\n";
  connection_ = std::thread([this]() { ProcessConnection(); });
  connection_.detach();
  is_active_ = true;
}

void DefaultClient::Disconnect() {
  if (is_active_) {
    Send(QuitMessage().Serialization());
    is_active_ = false;
  }
}

std::string DefaultClient::Send(const std::string& message) {
  {
    std::lock_guard guard(mutex_);
    messages_.push_back(message);
  }
  cond_variable_.notify_one();
  std::unique_lock lock(mutex_for_cond_var_);
  cond_variable_.wait(lock);
  return answer_;
}

void DefaultClient::ProcessConnection() {
  std::string message;
  char buf[256];
  while (is_active_) {
    std::unique_lock lock(mutex_for_cond_var_);
    if (messages_.empty()) {
      cond_variable_.wait(lock);
    }
    {
      std::lock_guard quard(mutex_);
      message = messages_.front();
      messages_.pop_front();
    }
    if (write(*client_discriptor_, message.c_str(), message.size()) < 0) {
      throw std::runtime_error("error while writing to socket folder");
    }
    bzero((char*)&buf, sizeof(buf));
    if (read(*client_discriptor_, &buf, sizeof(buf)) < 0) {
      throw std::runtime_error("error while reading from socket folder");
    }
    answer_ = buf;

    std::cout << answer_ << std::endl;
    if (answer_ == std::to_string(SerializationConstants::quit_response_id)) {
      is_active_ = false;
    }
    cond_variable_.notify_one();
  }
}
