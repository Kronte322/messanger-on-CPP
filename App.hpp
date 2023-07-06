#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Client.hpp"
#include "UI.hpp"

class App {
 public:
  App();

  void ProcessMainLoop();

 private:
  void SendMessage(const ClientMessage& message);

  sf::RenderWindow window_;
  sf::Font font_;
  Client client_;
  UI ui_;
  int id_identifier_;
};