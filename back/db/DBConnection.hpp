#pragma once

#include <pqxx/pqxx>
#include <string>

class DBConnection {
 public:
  DBConnection();

  ~DBConnection();

  pqxx::result ExecuteLogIn(const std::string& user_name,
                            const std::string& password_hash) const;

  void ExecuteSignUp(const std::string& user_name,
                     const std::string& password_hash) const;

  void ExecuteAddMessage(const std::string& text, int sender_id,
                         int receiver_id) const;

 private:
  pqxx::result Execute(const std::string& query) const;

  mutable pqxx::connection connection_;
};