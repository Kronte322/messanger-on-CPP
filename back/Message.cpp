#include "Message.hpp"

#include <iterator>
#include <sstream>

TextMessage::TextMessage(int sender_id, int receiver_id,
                         const std::string& text)
    : text_(text), sender_id_(sender_id), receiver_id_(receiver_id) {}

std::string TextMessage::Serialization() {
  return std::to_string(SerializationConstants::text_message_id) + " " +
         std::to_string(sender_id_) + " " + std::to_string(receiver_id_) + " " +
         std::to_string(text_.size()) + " " + text_ + '\0';
}

TextMessage::~TextMessage() = default;

SignUpMessage::SignUpMessage(const std::string& user_name,
                             const std::string& password_hash)
    : user_name_(user_name), password_hash_(password_hash) {}

std::string SignUpMessage::Serialization() {
  return std::to_string(SerializationConstants::sign_up_message_id) + " " +
         user_name_ + " " + password_hash_ + " " + '\0';
}

SignUpMessage::~SignUpMessage() = default;

LogInMessage::LogInMessage(const std::string& user_name,
                           const std::string& password_hash)
    : user_name_(user_name), password_hash_(password_hash) {}

std::string LogInMessage::Serialization() {
  return std::to_string(SerializationConstants::log_in_message_id) + " " +
         user_name_ + " " + password_hash_ + " " + '\0';
}

LogInMessage::~LogInMessage() = default;

QuitMessage::QuitMessage() = default;

std::string QuitMessage::Serialization() {
  return std::to_string(SerializationConstants::quit_message_id);
}

QuitMessage::~QuitMessage() = default;

TextResponse::TextResponse(int code_of_response)
    : code_of_response_(code_of_response) {}

std::string TextResponse::Serialization() {
  return std::to_string(SerializationConstants::text_response_id) + " " +
         std::to_string(code_of_response_) + " " + '\0';
}

TextResponse::~TextResponse() = default;

SignUpResponse::SignUpResponse(int code_of_response)
    : code_of_response_(code_of_response) {}

std::string SignUpResponse::Serialization() {
  return std::to_string(SerializationConstants::sign_up_response_id) + " " +
         std::to_string(code_of_response_) + " " + '\0';
}

SignUpResponse::~SignUpResponse() = default;

LogInResponse::LogInResponse(int id) : id_(id) {}

std::string LogInResponse::Serialization() {
  return std::to_string(SerializationConstants::log_in_response_id) + " " +
         "#" + std::to_string(id_) + " " + '\0';
}

LogInResponse::~LogInResponse() = default;

QuitResponse::QuitResponse() = default;

std::string QuitResponse::Serialization() {
  return std::to_string(SerializationConstants::quit_response_id);
}

QuitResponse::~QuitResponse() = default;
