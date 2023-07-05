#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <exception>
#include <iostream>
#include <thread>

#include "AppConstants.hpp"
#include "Button.hpp"
#include "Client.hpp"
#include "TextBox.hpp"

namespace ClientActionConstants {
const std::string log_in_id = "!log_in";
const std::string sign_in_id = "!sign_in";
const std::string text_id = "!text";
}  // namespace ClientActionConstants

void SetMessage(Client& client, const Message& message) {
  client.SetMessage() = std::unique_ptr<Message>(message.GetCopy());
  client.SetConditionVariable().notify_one();
}

void func() {}

int main(int argc, char* argv[]) {
  // int port_of_the_server = atoi(argv[1]);
  int port_of_the_server = 5555;
  Client client("127.0.0.1", port_of_the_server);
  try {
    client.Connect();
    std::thread(&Client::ProcessConnection, &client).detach();
  } catch (const std::string& str) {
    std::cout << str;
  }

  sf::RenderWindow window(
      sf::VideoMode(AppConstants::kWindowSizeX, AppConstants::kWindowSizeY),
      AppConstants::kTitle);

  window.setFramerateLimit(AppConstants::kFPS);

  sf::Font font;
  font.loadFromFile("../font/OpenSans-Bold.ttf");

  TextBox log_in_text_box(font, std::string("user name"), sf::Color::White,
                          sf::Color::White, 20, sf::Vector2f(100, 100),
                          sf::Vector2f(10, 10), 30, false, false);

  TextBox password_text_box(font, std::string("password"), sf::Color::White,
                            sf::Color::White, 20, sf::Vector2f(100, 150),
                            sf::Vector2f(10, 10), 30, true, false);

  Button<> button(
      sf::Vector2f(200, 100), sf::Vector2f(50, 50), sf::Color(108, 108, 255),
      []() { std::cout << "Pressed\n"; }, false);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      log_in_text_box.Update(window, event);
      password_text_box.Update(window, event);
      int interm = 5;
      button.Update(window, event);
    }

    window.clear(sf::Color::White);
    log_in_text_box.Draw(window);
    password_text_box.Draw(window);
    button.Draw(window);
    window.display();
  }
}