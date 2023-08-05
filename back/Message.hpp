#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "Server.hpp"

namespace SerializationConstants {
const int text_message_id = 1;
const int log_in_message_id = 2;
const int sign_up_message_id = 3;
const int quit_message_id = 7;
const int text_response_id = 4;
const int log_in_response_id = 5;
const int sign_up_response_id = 6;
const int quit_response_id = 8;
}  // namespace SerializationConstants

class BaseMessage {
 public:
  virtual std::string Serialization() = 0;

  virtual ~BaseMessage() = default;

 private:
};

class TextMessage : public BaseMessage {
 public:
  TextMessage(int sender_id, int receiver_id, const std::string& text);

  std::string Serialization() override;

  ~TextMessage();

 private:
  std::string text_;
  int sender_id_ = 0;
  int receiver_id_ = 0;
};

class SignUpMessage : public BaseMessage {
 public:
  SignUpMessage(const std::string& user_name, const std::string& password_hash);

  std::string Serialization() override;

  ~SignUpMessage();

 private:
  std::string user_name_;
  std::string password_hash_;
};

class LogInMessage : public BaseMessage {
 public:
  LogInMessage(const std::string& user_name, const std::string& password_hash);

  std::string Serialization() override;

  ~LogInMessage();

 private:
  std::string user_name_;
  std::string password_hash_;
};

class QuitMessage : public BaseMessage {
 public:
  QuitMessage();

  std::string Serialization() override;

  ~QuitMessage();

 private:
};

class TextResponse : public BaseMessage {
 public:
  TextResponse(int code_of_respones);

  std::string Serialization() override;

  ~TextResponse();

 private:
  int code_of_response_;
};

class SignUpResponse : public BaseMessage {
 public:
  SignUpResponse(int code_of_response);

  std::string Serialization() override;

  ~SignUpResponse();

 private:
  int code_of_response_;
};

class LogInResponse : public BaseMessage {
 public:
  LogInResponse(int id);

  std::string Serialization() override;

  ~LogInResponse();

 private:
  int id_;
};

class QuitResponse : public BaseMessage {
 public:
  QuitResponse();

  std::string Serialization() override;

  ~QuitResponse();

 private:
};
