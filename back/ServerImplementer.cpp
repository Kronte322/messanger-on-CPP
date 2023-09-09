#include "./ServerImplementer.hpp"

#include "../back/Message.hpp"

using namespace SerializationConstants;

ServerImplementer::ServerImplementer() {
  actions_ = {
      std::make_pair(sign_up_message_id, &ServerImplementer::ImplementSignUp),
      std::make_pair(log_in_message_id, &ServerImplementer::ImplementLogIn),
      std::make_pair(quit_message_id, &ServerImplementer::ImplementQuit),
      std::make_pair(get_user_id_message_id,
                     &ServerImplementer::ImplementGetUserId),
      std::make_pair(text_message_id, &ServerImplementer::ImplementTextMessage),
      std::make_pair(get_messages_message_id,
                     &ServerImplementer::ImplementGetMessages)};
}

std::string ServerImplementer::Implement(const std::string& message,
                                         DBConnection& db_connection) {
  std::istringstream stream(message);

  int id_of_message = 0;
  stream >> id_of_message;
  return actions_.at(id_of_message)(
      std::string(std::istreambuf_iterator<char>(stream), {}), db_connection);
}

std::string ServerImplementer::ImplementSignUp(std::string message,
                                               DBConnection& db_connection) {
  std::string user_name = GetString(message);
  std::string password = GetString(message);
  try {
    db_connection.ExecuteSignUp(user_name, password);
  } catch (const std::exception& except) {
    std::cout << except.what();
    return SignUpResponse(-1).Serialization();
  }
  return SignUpResponse(-2).Serialization();
}

std::string ServerImplementer::ImplementLogIn(std::string message,
                                              DBConnection& db_connection) {
  std::string user_name = GetString(message);
  std::string password = GetString(message);
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

std::string ServerImplementer::ImplementQuit(std::string message,
                                             DBConnection& db_connection) {
  return QuitResponse().Serialization();
}

std::string ServerImplementer::ImplementGetUserId(std::string message,
                                                  DBConnection& db_connection) {
  std::string user_name = GetString(message);
  int user_id = -1;
  try {
    auto res = db_connection.ExecuteGetUserId(user_name);
    for (const auto& row : res) {
      for (const auto& field : row) {
        std::cout << field.c_str() << '\t';
        field.to(user_id);
      }
    }
  } catch (const std::exception& except) {
    std::cout << except.what();
  }
  return GetUserIdResponse(user_id).Serialization();
}

std::string ServerImplementer::ImplementTextMessage(
    std::string message, DBConnection& db_connection) {
  int sender_id = GetInt(message);
  int receiver_id = GetInt(message);
  std::string text = GetString(message);
  int code = 1;
  try {
    auto res = db_connection.ExecuteSendMessage(sender_id, receiver_id, text);
  } catch (const std::exception& except) {
    std::cout << except.what();
    code = -1;
  }
  return TextResponse(code).Serialization();
}

std::string ServerImplementer::ImplementGetMessages(
    std::string message, DBConnection& db_connection) {
  int sender_id = GetInt(message);
  int receiver_id = GetInt(message);
  auto first_messages =
      db_connection.ExecuteGetMessages(sender_id, receiver_id);
  auto second_messages =
      db_connection.ExecuteGetMessages(receiver_id, sender_id);
  std::vector<std::pair<std::string, std::string>> messages;
  for (const auto& row : first_messages) {
    messages.emplace_back(row[0].as<std::string>(), row[1].as<std::string>());
  }
  messages.emplace_back("", "");
  for (const auto& row : second_messages) {
    messages.emplace_back(row[0].as<std::string>(), row[1].as<std::string>());
  }
  return GetMessagesResponse(messages).Serialization();
}