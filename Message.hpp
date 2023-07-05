#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "Server.hpp"

namespace SerializationConstants {
const int text_message_id = 1;
const int log_in_message_id = 2;
const int sign_in_message_id = 3;
}  // namespace SerializationConstants

class Message {
 public:
  virtual void Implement(Server&) = 0;

  virtual std::string Serialization() = 0;

  static std::unique_ptr<Message> Deserialization(
      const std::string& serialized_string);

  virtual Message* GetCopy() const = 0;

  virtual ~Message() {}

 private:
  static const std::unordered_map<
      int, std::function<std::unique_ptr<Message>(const std::string&)>>
      actions_;
};

class TextMessage : public Message {
 public:
  TextMessage(const std::string& text, int sender_id, int receiver_id);

  void Implement(Server& server) override;

  std::string Serialization() override;

  static std::unique_ptr<Message> Deserialization(
      const std::string& serialized_string);

  Message* GetCopy() const override;

  ~TextMessage();

 private:
  std::string text_;
  int sender_id_ = 0;
  int receiver_id_ = 0;
};

class SignInMessage : public Message {
 public:
  SignInMessage(const std::string& user_name, const std::string& password_hash);

  void Implement(Server& server) override;

  std::string Serialization() override;

  static std::unique_ptr<Message> Deserialization(
      const std::string& serialized_string);

  Message* GetCopy() const override;

  ~SignInMessage();

 private:
  std::string user_name_;
  std::string password_hash_;
};

class LogInMessage : public Message {
 public:
  LogInMessage(const std::string& user_name, const std::string& password_hash);

  void Implement(Server& server) override;

  std::string Serialization() override;

  static std::unique_ptr<Message> Deserialization(
      const std::string& serialized_string);

  Message* GetCopy() const override;

  ~LogInMessage();

 private:
  std::string user_name_;
  std::string password_hash_;
};