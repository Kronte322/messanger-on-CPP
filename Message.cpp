#include "Message.hpp"

#include "DBConnection.hpp"

TextMessage::TextMessage(const std::string& text, int receiver_id,
                         int sender_id)
    : text_(text), sender_id_(sender_id), receiver_id_(receiver_id) {}

void TextMessage::Implement(Server& server) {
  server.GetDbConnection().ExecuteAddMessage(text_, sender_id_, receiver_id_);
}

TextMessage::~TextMessage() = default;

SignInMessage::SignInMessage(const std::string& user_name,
                             const std::string& password_hash)
    : user_name_(user_name), password_hash_(password_hash) {}
void SignInMessage::Implement(Server& server) {
  server.GetDbConnection().ExecuteSignIn(user_name_, password_hash_);
}
SignInMessage::~SignInMessage() {}

LogInMessage::LogInMessage(const std::string& user_name,
                           const std::string& password_hash)
    : user_name_(user_name), password_hash_(password_hash) {}
void LogInMessage::Implement(Server& server) {
  server.GetDbConnection().ExecuteLogIn(user_name_, password_hash_);
}
LogInMessage::~LogInMessage() {}

int main() {}