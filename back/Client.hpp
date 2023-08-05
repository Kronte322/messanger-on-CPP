#pragma once
#include <netinet/in.h>

#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <string>

class App;

class Client {
 public:
  virtual void Connect(const std::string& ip_address, int port) = 0;
  virtual void Disconnect() = 0;
  virtual ~Client() = default;
};

class SendClient : public Client {
 public:
  virtual void Send(const std::string& message) = 0;
};

class BasicClient : public Client {
 public:
  virtual std::string Send(const std::string& message) = 0;
};

class DefaultClient : public BasicClient {
 public:
  DefaultClient();

  ~DefaultClient();

  void Connect(const std::string& ip_address, int port) override;

  void Disconnect() override;

  std::string Send(const std::string& message) override;

 private:
  void ProcessConnection();

  std::thread connection_;
  std::mutex mutex_for_cond_var_;
  std::mutex mutex_;
  std::condition_variable cond_variable_;
  std::deque<std::string> messages_;
  std::string answer_;
  sockaddr_in server_address_;
  std::shared_ptr<int> client_discriptor_;
  bool is_active_ = false;
};