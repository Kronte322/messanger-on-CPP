#pragma once

#include <iostream>

std::string SignUpSql(const std::string& user_name,
                      const std::string& password);

std::string LogInSql(const std::string& user_name, const std::string& password);

std::string SendMessageSql(int sender_id, int receiver_id,
                           const std::string& message, const std::string& time);

std::string GetIdMessageSql(const std::string& user_name);

std::string GetPresentTimeSql();

std::string GetMessagesSql(int sender_id, int receiver_id);