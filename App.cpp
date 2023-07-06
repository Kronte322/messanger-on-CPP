#include "App.hpp"

#include "AppConstants.hpp"

App::App()
    : window_(
          sf::VideoMode(AppConstants::kWindowSizeX, AppConstants::kWindowSizeY),
          AppConstants::kTitle),
      client_("127.0.0.1", 5555) {
  try {
    client_.Connect();
    std::thread(&Client::ProcessConnection, &client_).detach();
  } catch (const std::string& str) {
    std::cout << str;
  }
  window_.setFramerateLimit(60);
  font_.loadFromFile("../font/OpenSans-Bold.ttf");
  ui_ = UI(font_);
  ui_.SetLogInScene();
}

void App::ProcessMainLoop() {
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      }
      ui_.Update(window_, event);
    }

    window_.clear(sf::Color::White);
    ui_.Draw(window_);
    window_.display();
  }
}

void App::SendMessage(const ClientMessage& message) {
  client_.SetMessage() = std::unique_ptr<ClientMessage>(message.GetCopy());
  client_.SetConditionVariable().notify_one();
}