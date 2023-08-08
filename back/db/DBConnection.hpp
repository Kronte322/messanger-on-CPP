#pragma once

#include <pqxx/pqxx>
#include <string>

class DBConnection {
 public:
  DBConnection();

  ~DBConnection();

  pqxx::result ExecuteLogIn(const std::string& user_name,
                            const std::string& password_hash) const;

  pqxx::result ExecuteSignUp(const std::string& user_name,
                             const std::string& password_hash) const;

  pqxx::result ExecuteSendMessage(int sender_id, int receiver_id,
                                  const std::string& text) const;

  pqxx::result ExecuteGetUserId(const std::string& user_name) const;

 private:
  pqxx::result Execute(const std::string& query) const;

  mutable pqxx::connection connection_;
};