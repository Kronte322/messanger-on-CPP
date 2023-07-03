#include "Message.hpp"

#include <iterator>
#include <sstream>

#include "DBConnection.hpp"

const std::unordered_map<
    int, std::function<std::unique_ptr<Message>(const std::string&)>>
    Message::actions_ = {std::make_pair(SerializationConstants::text_message_id,
                                        TextMessage::Deserialization)};

std::unique_ptr<Message> Message::Deserialization(
    const std::string& serialized_string) {
  std::istringstream stream(serialized_string);
  int id_of_message = 0;
  stream >> id_of_message;
  return Message::actions_.at(id_of_message)(
      std::string(std::istreambuf_iterator<char>(stream), {}));
}

TextMessage::TextMessage(const std::string& text, int sender_id,
                         int receiver_id)
    : text_(text), sender_id_(sender_id), receiver_id_(receiver_id) {}

void TextMessage::Implement(Server& server) {
  server.GetDbConnection().ExecuteAddMessage(text_, sender_id_, receiver_id_);
}

// void TextMessage::Implement(Server& server) {
//   server.SetMessages().push_back(text_);
// }

std::string TextMessage::Serialization() {
  return std::to_string(SerializationConstants::text_message_id) + " " +
         std::to_string(sender_id_) + " " + std::to_string(receiver_id_) + " " +
         std::to_string(text_.size()) + " " + text_ + '\0';
}

std::unique_ptr<Message> TextMessage::Deserialization(
    const std::string& serialized_string) {
  std::istringstream stream(serialized_string);
  int sender_id = 0;
  int receiver_id = 0;
  int size_of_message = 0;

  stream >> sender_id >> receiver_id >> size_of_message;
  stream.get();
  std::string text(std::string(std::istreambuf_iterator<char>(stream), {}));
  return std::unique_ptr<Message>(
      new TextMessage(text, sender_id, receiver_id));
  // return std::make_unique<Message>(TextMessage(text, sender_id,
  // receiver_id));
}

TextMessage::~TextMessage() = default;

SignInMessage::SignInMessage(const std::string& user_name,
                             const std::string& password_hash)
    : user_name_(user_name), password_hash_(password_hash) {}

void SignInMessage::Implement(Server& server) {
  server.GetDbConnection().ExecuteSignIn(user_name_, password_hash_);
}

std::string SignInMessage::Serialization() { return ""; }

SignInMessage::~SignInMessage() {}

LogInMessage::LogInMessage(const std::string& user_name,
                           const std::string& password_hash)
    : user_name_(user_name), password_hash_(password_hash) {}

void LogInMessage::Implement(Server& server) {
  server.GetDbConnection().ExecuteLogIn(user_name_, password_hash_);
}

std::string LogInMessage::Serialization() { return ""; }

LogInMessage::~LogInMessage() {}
