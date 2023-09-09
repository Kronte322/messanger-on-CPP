#include "SqlQueries.hpp"

std::string SignUpSql(const std::string& user_name,
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
                           const std::string& message,
                           const std::string& date) {
  return std::string(
             "INSERT INTO st.message(sender, receiver, message, time) VALUES "
             "(") +
         std::to_string(sender_id) + ", " + std::to_string(receiver_id) + ", " +
         "'" + message + "'" + ", '" + date + "'" + ");";
}

std::string GetIdMessageSql(const std::string& user_name) {
  return std::string("SELECT user_id FROM st.user WHERE user_name = '") +
         user_name + "'";
}

std::string GetPresentTimeSql() { return std::string("Select NOW()"); }

std::string GetMessagesSql(int sender_id, int receiver_id) {
  return std::string("SELECT time, message FROM st.message WHERE sender = ") +
         std::to_string(sender_id) + " AND " +
         "receiver = " + std::to_string(receiver_id);
}