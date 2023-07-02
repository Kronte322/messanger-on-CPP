#pragma once

#include <pqxx/pqxx>
#include <string>

class DBConnection {
 public:
  DBConnection();

  ~DBConnection();

  void ExecuteLogIn(const std::string& user_name,
                    const std::string& password_hash) const;

  void ExecuteSignIn(const std::string& user_name,
                     const std::string& password_hash) const;

  void ExecuteAddMessage(const std::string& text, int sender_id,
                         int receiver_id) const;

 private:
  void Execute(const std::string& query) const;

  pqxx::connection connection_;
  mutable pqxx::work worker_;
};