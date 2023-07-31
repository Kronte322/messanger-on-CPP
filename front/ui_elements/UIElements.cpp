#include "UIElements.hpp"

#include <iostream>

using namespace LogInUiConstants;
using namespace AppConstants;

LogInElement::LogInElement(sf::Vector2f position, sf::Font& font)
    : user_name_(font, {kPositionForUsername.x + position.x,
                        kPositionForUsername.y + position.y}),
      password_(font, {kPositionForPassword.x + position.x,
                       kPositionForPassword.y + position.y}),
      log_in_(
          font,
          [this]() {
            std::cout << user_name_.GetEnteredText() << ' '
                      << password_.GetEnteredText() << std::endl;
          },
          false, kNameOfLogInButton,
          {kPositionForLogInButton.x + position.x,
           kPositionForLogInButton.y + position.y},
          kSizeOfCharForLogInButton),
      sign_up_(
          font, []() { std::cout << "Pressed\n"; }, false, kNameOfSignInButton,
          {kPositionForSignInButton.x + position.x,
           kPositionForSignInButton.y + position.y},
          kSizeOfCharForSignInButton) {}

void LogInElement::Update(sf::RenderWindow& window, sf::Event& event) {
  user_name_.Update(window, event);
  password_.Update(window, event);
  log_in_.Update(window, event);
  sign_up_.Update(window, event);
}

void LogInElement::Draw(sf::RenderWindow& window) {
  user_name_.Draw(window);
  password_.Draw(window);
  log_in_.Draw(window);
  sign_up_.Draw(window);
}