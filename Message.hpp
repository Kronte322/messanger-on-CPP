#pragma once

#include <iostream>

#include "Server.hpp"

class Message {
 public:
  virtual void Implement(Server&) = 0;
  virtual ~Message() {}
};

class TextMessage : public Message {
 public:
  TextMessage(const std::string& text, int sender_id, int receiver_id);
  void Implement(Server& server);
  ~TextMessage();

 private:
  std::string text_;
  int sender_id_ = 0;
  int receiver_id_ = 0;
};

class SignInMessage : public Message {
 public:
  SignInMessage(const std::string& user_name, const std::string& password_hash);
  void Implement(Server& server);
  ~SignInMessage();

 private:
  std::string user_name_;
  std::string password_hash_;
};

class LogInMessage : public Message {
 public:
  LogInMessage(const std::string& user_name, const std::string& password_hash);
  void Implement(Server& server);
  ~LogInMessage();

 private:
  std::string user_name_;
  std::string password_hash_;
};