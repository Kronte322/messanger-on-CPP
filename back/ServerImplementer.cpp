#include "./ServerImplementer.hpp"

#include "../back/Message.hpp"

using namespace SerializationConstants;

ServerImplementer::ServerImplementer() {
  actions_ = {
      std::make_pair(sign_up_message_id, &ServerImplementer::ImplementSignUp),
      std::make_pair(log_in_message_id, &ServerImplementer::ImplementLogIn),
      std::make_pair(quit_message_id, &ServerImplementer::ImplementQuit)};
}

std::string ServerImplementer::Implement(const std::string& message,
                                         DBConnection& db_connection) {
  std::istringstream stream(message);

  int id_of_message = 0;
  stream >> id_of_message;
  return actions_.at(id_of_message)(
      std::string(std::istreambuf_iterator<char>(stream), {}), db_connection);
}

std::string ServerImplementer::ImplementSignUp(const std::string& message,
                                               DBConnection& db_connection) {
  std::istringstream stream(message);
  std::string user_name;
  std::string password;
  stream >> user_name >> password;
  try {
    db_connection.ExecuteSignUp(user_name, password);
  } catch (const std::exception& except) {
    std::cout << except.what();
    return SignUpResponse(-1).Serialization();
  }
  return SignUpResponse(-2).Serialization();
}

std::string ServerImplementer::ImplementLogIn(const std::string& message,
                                              DBConnection& db_connection) {
  std::istringstream stream(message);
  std::string user_name;
  std::string password;
  stream >> user_name >> password;
  int user_id = -1;
  try {
    auto res = db_connection.ExecuteLogIn(user_name, password);
    for (const auto& row : res) {
      for (const auto& field : row) {
        std::cout << field.c_str() << '\t';
        field.to(user_id);
      }
    }
  } catch (const std::exception& except) {
    std::cout << except.what();
  }
  return LogInResponse(user_id).Serialization();
}

std::string ServerImplementer::ImplementQuit(const std::string& message,
                                             DBConnection& db_connection) {
  return QuitResponse().Serialization();
}