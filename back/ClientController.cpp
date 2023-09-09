#include "./ClientController.hpp"

#include "../back/Message.hpp"

ClientController::ClientController(DefaultClient& client, ClientStorage& data,
                                   ClientImplementer& implementer)
    : client_(client), data_(data), implementer_(implementer) {}

int ClientController::SendSignUpMessage(const std::string& user_name,
                                        const std::string& password) {
  auto message = SignUpMessage(user_name, password);
  auto response = client_.Send(message.Serialization());
  return implementer_.Implement(response, data_);
}

int ClientController::SendLogInMessage(const std::string& user_name,
                                       const std::string& password) {
  auto message = LogInMessage(user_name, password);
  auto response = client_.Send(message.Serialization());
  return implementer_.Implement(response, data_);
}

int ClientController::SendGetUserIdMessage(const std::string& user_name) {
  auto message = GetUserIdMessage(user_name);
  auto response = client_.Send(message.Serialization());
  return implementer_.Implement(response, data_);
}

int ClientController::SendTextMessage(int sender_id, int receiver_id,
                                      const std::string& text) {
  auto message = TextMessage(sender_id, receiver_id, text);
  auto response = client_.Send(message.Serialization());
  return implementer_.Implement(response, data_);
}

int ClientController::SendGetMessagesMessage(int sender_id, int receiver_id) {
  auto message = GetMessagesMessage(sender_id, receiver_id);
  auto response = client_.Send(message.Serialization());
  return implementer_.Implement(response, data_);
}