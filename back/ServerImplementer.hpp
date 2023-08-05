#pragma once
#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>

#include "../back/db/DBConnection.hpp"
class ServerImplementer {
 public:
  ServerImplementer();
  std::string Implement(const std::string& message,
                        DBConnection& db_connection);

 private:
  static std::string ImplementSignUp(const std::string& message,
                                     DBConnection& db_connection);

  static std::string ImplementLogIn(const std::string& message,
                                    DBConnection& db_connection);

  static std::string ImplementQuit(const std::string& message,
                                   DBConnection& db_connection);

  std::unordered_map<
      int, std::function<std::string(const std::string&, DBConnection&)>>
      actions_;
};