#include "SqlQueries.hpp"

std::string SignInSql(const std::string& user_name,
                      const std::string& password_cache) {
  return std::string(
             "INSERT INTO st.user(user_name, password_cache) VALUES (") +
         "'" + user_name + "'" + ", " + "'" + password_cache + "'" + ");";
}

std::string LogInSql(const std::string& user_name,
                     const std::string& password_cache) {
  return std::string("SELECT user_id FROM st.user WHERE user_name = ") + "'" +
         user_name + "'" + " AND " + "password_cache = '" + password_cache +
         "'";
}

std::string SendMessageSql(int sender_id, int receiver_id,
                           const std::string& message) {
  return std::string(
             "INSERT INTO st.message(sender, receiver, message) VALUES (") +
         std::to_string(sender_id) + ", " + std::to_string(receiver_id) + ", " +
         "'" + message + "'" + ");";
}
