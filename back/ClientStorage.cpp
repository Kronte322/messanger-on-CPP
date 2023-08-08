#include "./ClientStorage.hpp"

int& ClientStorage::SetUserId() { return user_id_; }

int& ClientStorage::SetReceiverId() { return receiver_id_; }

std::vector<std::string>& ClientStorage::SetMessages() { return messages_; }
