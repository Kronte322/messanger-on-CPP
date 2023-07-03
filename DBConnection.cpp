#include "DBConnection.hpp"

#include "SqlQueries.hpp"

DBConnection::DBConnection()
    : connection_(
          "dbname = postgres user = postgres password = antisocialplayer \
      hostaddr = 192.168.0.108 port = 5432") {}

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
  pqxx::work l_work(connection_);
  try {
    l_work.exec(query);
    l_work.commit();
  } catch (const std::exception& except) {
    std::cout << except.what();
    l_work.abort();
    throw;
  }
}

DBConnection::~DBConnection() { connection_.disconnect(); }
