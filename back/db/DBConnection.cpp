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

pqxx::result DBConnection::ExecuteSignUp(
    const std::string& user_name, const std::string& password_hash) const {
  return Execute(SignUpSql(user_name, password_hash));
}

pqxx::result DBConnection::ExecuteSendMessage(int sender_id, int receiver_id,
                                              const std::string& text) const {
  return Execute(SendMessageSql(sender_id, receiver_id, text));
}

pqxx::result DBConnection::ExecuteGetUserId(
    const std::string& user_name) const {
  return Execute(GetIdMessageSql(user_name));
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
