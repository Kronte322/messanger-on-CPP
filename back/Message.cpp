#include "Message.hpp"

#include <iterator>
#include <sstream>

int GetInt(std::string& message) {
  int res = 0;
  bool sign = false;
  size_t begin = 0;
  size_t end = 0;
  size_t i = 0;
  for (; i < message.size(); ++i) {
    if (message[i] == '#') {
      if (sign) {
        end = i;
        break;
      } else {
        sign = true;
        begin = i + 1;
      }
    }
  }
  std::string interm = message.substr(begin, end - begin);
  if (end == message.size() - 1) {
    message.clear();
  } else {
    message = message.substr(end + 1, message.size() - end - 1);
  }
  return std::stoi(interm);
}

std::string GetString(std::string& message) {
  std::string res;
  bool sign = false;
  size_t begin = 0;
  size_t end = 0;
  size_t i = 0;
  for (; i < message.size(); ++i) {
    if (message[i] == '#') {
      if (sign) {
        end = i;
        break;
      } else {
        sign = true;
        begin = i + 1;
      }
    }
  }
  res = message.substr(begin, end - begin);
  if (end == message.size() - 1) {
    message.clear();
  } else {
    message = message.substr(end + 1, message.size() - end - 1);
  }
  return res;
}

TextMessage::TextMessage(int sender_id, int receiver_id,
                         const std::string& text)
    : text_(text), sender_id_(sender_id), receiver_id_(receiver_id) {}

std::string TextMessage::Serialization() {
  return std::to_string(SerializationConstants::text_message_id) + "#" +
         std::to_string(sender_id_) + "##" + std::to_string(receiver_id_) +
         "##" + text_ + "#";
}

TextMessage::~TextMessage() = default;

SignUpMessage::SignUpMessage(const std::string& user_name,
                             const std::string& password_hash)
    : user_name_(user_name), password_hash_(password_hash) {}

std::string SignUpMessage::Serialization() {
  return std::to_string(SerializationConstants::sign_up_message_id) + "#" +
         user_name_ + "##" + password_hash_ + "#";
}

SignUpMessage::~SignUpMessage() = default;

LogInMessage::LogInMessage(const std::string& user_name,
                           const std::string& password_hash)
    : user_name_(user_name), password_hash_(password_hash) {}

std::string LogInMessage::Serialization() {
  return std::to_string(SerializationConstants::log_in_message_id) + "#" +
         user_name_ + "##" + password_hash_ + "#";
}

LogInMessage::~LogInMessage() = default;

QuitMessage::QuitMessage() = default;

std::string QuitMessage::Serialization() {
  return std::to_string(SerializationConstants::quit_message_id);
}

QuitMessage::~QuitMessage() = default;

GetUserIdMessage::GetUserIdMessage(const std::string& user_name)
    : user_name_(user_name) {}

std::string GetUserIdMessage::Serialization() {
  return std::to_string(SerializationConstants::get_user_id_message_id) + "#" +
         user_name_ + "#";
}

GetUserIdMessage::~GetUserIdMessage() = default;

TextResponse::TextResponse(int code_of_response)
    : code_of_response_(code_of_response) {}

std::string TextResponse::Serialization() {
  return std::to_string(SerializationConstants::text_response_id) + "#" +
         std::to_string(code_of_response_) + "#";
}

TextResponse::~TextResponse() = default;

SignUpResponse::SignUpResponse(int code_of_response)
    : code_of_response_(code_of_response) {}

std::string SignUpResponse::Serialization() {
  return std::to_string(SerializationConstants::sign_up_response_id) + "#" +
         std::to_string(code_of_response_) + "#";
}

SignUpResponse::~SignUpResponse() = default;

LogInResponse::LogInResponse(int id) : id_(id) {}

std::string LogInResponse::Serialization() {
  return std::to_string(SerializationConstants::log_in_response_id) + "#" +
         std::to_string(id_) + "#";
}

LogInResponse::~LogInResponse() = default;

QuitResponse::QuitResponse() = default;

std::string QuitResponse::Serialization() {
  return std::to_string(SerializationConstants::quit_response_id);
}

QuitResponse::~QuitResponse() = default;

GetUserIdResponse::GetUserIdResponse(int id) : id_(id) {}

std::string GetUserIdResponse::Serialization() {
  return std::to_string(SerializationConstants::get_user_id_response_id) + "#" +
         std::to_string(id_) + "#";
}

GetUserIdResponse::~GetUserIdResponse() = default;
