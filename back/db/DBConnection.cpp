#include "DBConnection.hpp"

#include "SqlQueries.hpp"

DBConnection::DBConnection()
    : connection_(
          "dbname = postgres user = postgres password = antisocialplayer \
      hostaddr = 127.0.0.1 port = 5432") {}

pqxx::result DBConnection::ExecuteLogIn(
    const std::string& user_name, const std::string& password_hash) const {
  return Execute(LogInSql(user_name, password_hash));
}

void DBConnection::ExecuteSignUp(const std::string& user_name,
                                 const std::string& password_hash) const {
  Execute(SignUpSql(user_name, password_hash));
}

void DBConnection::ExecuteAddMessage(const std::string& text, int sender_id,
                                     int receiver_id) const {
  Execute(SendMessageSql(sender_id, receiver_id, text));
}

pqxx::result DBConnection::Execute(const std::string& query) const {
  pqxx::work work(connection_);
  pqxx::result res;
  try {
    res = work.exec(query);
    work.commit();
  } catch (const std::exception& except) {
    std::cout << except.what();
    work.abort();
    throw;
  }
  return res;
}

DBConnection::~DBConnection() { connection_.disconnect(); }
