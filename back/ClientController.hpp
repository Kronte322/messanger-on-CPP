#include "../back/Client.hpp"

class ClientController {
 public:
  ClientController(DefaultClient& client);

 private:
  DefaultClient& client_;
};