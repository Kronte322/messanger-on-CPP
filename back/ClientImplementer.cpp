#include "./ClientImplementer.hpp"

#include "../back/Message.hpp"

using namespace SerializationConstants;

ClientImplementer::ClientImplementer() {
  actions_ = {
      std::make_pair(sign_up_response_id, &ClientImplementer::ImplementSignUp),
      std::make_pair(log_in_response_id, &ClientImplementer::ImplementLogIn),
      std::make_pair(quit_response_id, &ClientImplementer::ImplementQuit),
      std::make_pair(get_user_id_response_id,
                     &ClientImplementer::ImplementGetUserId),
      std::make_pair(text_response_id,
                     &ClientImplementer::ImplementSendMessage),
      std::make_pair(get_messages_response_id,
                     &ClientImplementer::ImplementGetMessages)};
}

int ClientImplementer::Implement(const std::string& message,
                                 ClientStorage& data) {
  std::istringstream stream(message);

  int id_of_message = 0;
  stream >> id_of_message;
  return actions_.at(id_of_message)(
      std::string(std::istreambuf_iterator<char>(stream), {}), data);
}

int ClientImplementer::ImplementSignUp(std::string message,
                                       ClientStorage& data) {
  int response = GetInt(message);
  return response;
}

int ClientImplementer::ImplementLogIn(std::string message,
                                      ClientStorage& data) {
  int id = GetInt(message);
  data.SetUserId() = id;
  return id;
}

int ClientImplementer::ImplementQuit(std::string message, ClientStorage& data) {
  return 1;
}

int ClientImplementer::ImplementGetUserId(std::string message,
                                          ClientStorage& data) {
  int id = GetInt(message);
  data.SetReceiverId() = id;
  return id;
}

int ClientImplementer::ImplementSendMessage(std::string message,
                                            ClientStorage& data) {
  int code = GetInt(message);
  return code;
}

int ClientImplementer::ImplementGetMessages(std::string message,
                                            ClientStorage& data) {
  decltype(auto) messages = data.SetMessages();
  messages.clear();
  while (!message.empty()) {
    auto date = GetString(message);
    auto text = GetString(message);
    messages.emplace_back(date, text);
  }
  return 1;
}
