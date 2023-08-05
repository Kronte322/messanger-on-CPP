#include "./ClientImplementer.hpp"

#include "../back/Message.hpp"

using namespace SerializationConstants;

ClientImplementer::ClientImplementer() {
  actions_ = {
      std::make_pair(sign_up_response_id, &ClientImplementer::ImplementSignUp),
      std::make_pair(log_in_response_id, &ClientImplementer::ImplementLogIn),
      std::make_pair(quit_response_id, &ClientImplementer::ImplementQuit)};
}

int ClientImplementer::Implement(const std::string& message,
                                 ClientStorage& data) {
  std::istringstream stream(message);

  int id_of_message = 0;
  stream >> id_of_message;

  stream.get();
  return actions_.at(id_of_message)(
      std::string(std::istreambuf_iterator<char>(stream), {}), data);
}

int ClientImplementer::ImplementSignUp(const std::string& message,
                                       ClientStorage& data) {
  std::istringstream stream(message);
  int response = 0;
  stream >> response;

  return response;
}

int ClientImplementer::ImplementLogIn(const std::string& message,
                                      ClientStorage& data) {
  std::istringstream stream(message);
  char interm = 0;
  int id = 0;
  stream >> interm;
  stream >> id;
  data.SetUserId() = id;
  return id;
}

int ClientImplementer::ImplementQuit(const std::string& message,
                                     ClientStorage& data) {
  return 1;
}