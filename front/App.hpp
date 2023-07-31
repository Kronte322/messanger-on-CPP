#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "../back/Client.hpp"
#include "../back/ClientStorage.hpp"
#include "../front/UI.hpp"

class App {
 public:
  App();

  void ProcessMainLoop();

  sf::Font& SetFont();

  int& SetUserId();

 private:
  void SendMessage(const ClientMessage& message);

  sf::RenderWindow window_;
  ClientStorage data_;
  sf::Font font_;
  Client client_;
  UI ui_;
  int id_identifier_;
};