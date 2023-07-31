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
const int text_response_id = 4;
const int log_in_response_id = 5;
const int sign_in_response_id = 6;
}  // namespace SerializationConstants

class Client;

class BaseMessage {
 public:
  virtual std::string Serialization() = 0;

  static std::unique_ptr<BaseMessage> Deserialization(
      const std::string& serialized_string);

  virtual ~BaseMessage() = default;

 private:
  static const std::unordered_map<
      int, std::function<std::unique_ptr<BaseMessage>(const std::string&)>>
      actions_;
};

class ClientMessage : public BaseMessage {
 public:
  virtual void Implement(Server&) = 0;

  virtual ClientMessage* GetCopy() const = 0;

  virtual ~ClientMessage() = default;

 private:
};

class TextMessage : public ClientMessage {
 public:
  TextMessage(const std::string& text, int sender_id, int receiver_id);

  void Implement(Server& server) override;

  std::string Serialization() override;

  static std::unique_ptr<BaseMessage> Deserialization(
      const std::string& serialized_string);

  ClientMessage* GetCopy() const override;

  ~TextMessage();

 private:
  std::string text_;
  int sender_id_ = 0;
  int receiver_id_ = 0;
};

class SignInMessage : public ClientMessage {
 public:
  SignInMessage(const std::string& user_name, const std::string& password_hash);

  void Implement(Server& server) override;

  std::string Serialization() override;

  static std::unique_ptr<BaseMessage> Deserialization(
      const std::string& serialized_string);

  ClientMessage* GetCopy() const override;

  ~SignInMessage();

 private:
  std::string user_name_;
  std::string password_hash_;
};

class LogInMessage : public ClientMessage {
 public:
  LogInMessage(const std::string& user_name, const std::string& password_hash);

  void Implement(Server& server) override;

  std::string Serialization() override;

  static std::unique_ptr<BaseMessage> Deserialization(
      const std::string& serialized_string);

  ClientMessage* GetCopy() const override;

  ~LogInMessage();

 private:
  std::string user_name_;
  std::string password_hash_;
};

class ServerMessage : public BaseMessage {
 public:
  ServerMessage() = default;

  virtual void Implement(Client& client) = 0;

  virtual ServerMessage* GetCopy() const = 0;

  virtual ~ServerMessage() = default;

 private:
};

class TextResponse : public ServerMessage {
 public:
  TextResponse(int code_of_respones);

  void Implement(Client& client) override;

  std::string Serialization() override;

  static std::unique_ptr<BaseMessage> Deserialization(
      const std::string& serialized_string);

  ServerMessage* GetCopy() const override;

  ~TextResponse();

 private:
  int code_of_response_;
};

class SignInResponse : public ServerMessage {
 public:
  SignInResponse(int code_of_response);

  void Implement(Client& client) override;

  std::string Serialization() override;

  static std::unique_ptr<BaseMessage> Deserialization(
      const std::string& serialized_string);

  ServerMessage* GetCopy() const override;

  ~SignInResponse();

 private:
  int code_of_response_;
};

class LogInResponse : public ServerMessage {
 public:
  LogInResponse(int id);

  void Implement(Client& client) override;

  std::string Serialization() override;

  static std::unique_ptr<BaseMessage> Deserialization(
      const std::string& serialized_string);

  ServerMessage* GetCopy() const override;

  ~LogInResponse();

 private:
  int id_;
};