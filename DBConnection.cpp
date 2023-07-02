#include "DBConnection.hpp"

#include "SqlQueries.hpp"

DBConnection::DBConnection()
    : connection_(
          "dbname = postgres user = postgres password = antisocialplayer \
      hostaddr = 192.168.0.108 port = 5432"),
      worker_(connection_) {}

void DBConnection::ExecuteLogIn(const std::string& user_name,
                                const std::string& password_hash) const {
  Execute(LogInSql(user_name, password_hash));
}

void DBConnection::ExecuteSignIn(const std::string& user_name,
                                 const std::string& password_hash) const {
  Execute(SignInSql(user_name, password_hash));
}

void DBConnection::ExecuteAddMessage(const std::string& text, int sender_id,
                                     int receiver_id) const {
  Execute(SendMessageSql(sender_id, receiver_id, text));
}

void DBConnection::Execute(const std::string& query) const {
  worker_.exec(query);
  worker_.commit();
}

DBConnection::~DBConnection() { connection_.disconnect(); }
