#include "App.hpp"

#include "../AppConstants.hpp"
#include "../front/ui_basic/TextBox.hpp"
#include "../front/ui_elements/ConstructElem.hpp"
#include "../front/ui_elements/UIElements.hpp"

App::App()
    : window_(
          sf::VideoMode(AppConstants::kWindowSizeX, AppConstants::kWindowSizeY),
          AppConstants::kTitle),
      client_("127.0.0.1", 5555, *this),
      ui_(font_) {
  try {
    client_.Connect();
    std::thread(&Client::ProcessConnection, &client_).detach();
  } catch (const std::string& str) {
    std::cout << str;
  }
  window_.setFramerateLimit(60);
  font_.loadFromFile("../sources/OpenSans-Bold.ttf");
  ui_.AddElement(ElementsIdentifiers::kLogInId,
                 GetElement<ElementsIdentifiers::kLogInId>(font_));
}

void App::ProcessMainLoop() {
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      }
      ui_.Update(window_, event, data_);
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

int& App::SetUserId() { return id_identifier_; }

sf::Font& App::SetFont() { return font_; }