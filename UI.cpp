#include "UI.hpp"

#include <iostream>

#include "AppConstants.hpp"

void UI::SetLogInScene() {
  using namespace LogInUiConstants;
  using namespace AppConstants;
  ClearUi();
  text_boxes_.emplace_back(font_, kBackGroundStringForUsername,
                           kDefaultColorForText, kColorForRectangleForUsername,
                           kSizeOfCharacterForUsername, kPositionForUsername,
                           sf::Vector2f(10, 10), kLimitOfCharsForUsername,
                           false, false);

  text_boxes_.emplace_back(font_, kBackGroundStringForPassword,
                           kDefaultColorForText, kColorForRectangleForPassword,
                           kSizeOfCharacterForPassword, kPositionForPassword,
                           sf::Vector2f(10, 10), kLimitOfCharsForPassword, true,
                           false);

  buttons_.push_back(TextButton<UI>(
      kNameOfLogInButton, font_, kSizeOfCharForLogInButton,
      kPositionForLogInButton, kColorForLogInButton, kColorTextForLogInButton,
      [](UI& ui) { std::cout << "Pressed\n"; }, false));

  buttons_.push_back(TextButton<UI>(
      kNameOfSignInButton, font_, kSizeOfCharForSignInButton,
      kPositionForSignInButton, kColorForSignInButton,
      kColorTextForSignInButton, [](UI& ui) { std::cout << "Pressed\n"; },
      false));
}

void UI::ClearUi() {
  text_boxes_.clear();
  buttons_.clear();
}

void UI::Update(sf::RenderWindow& window, sf::Event& event) {
  for (auto& item : text_boxes_) {
    item.Update(window, event);
  }
  for (auto& item : buttons_) {
    item.Update(window, event, *this);
  }
}

void UI::Draw(sf::RenderWindow& window) {
  for (auto& item : text_boxes_) {
    item.Draw(window);
  }
  for (auto& item : buttons_) {
    item.Draw(window);
  }
}

UI::UI(const sf::Font& font) : font_(font) {}
