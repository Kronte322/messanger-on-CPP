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