#pragma once
#include <SFML/Graphics.hpp>

namespace AppConstants {

const char kTitle[] = "Gold Messenger";

const int kFPS = 60;

const int kWindowSizeX = 800;

const int kWindowSizeY = 800;

const sf::Color kDefaultColorForText = sf::Color::White;
}  // namespace AppConstants
namespace ElementsIdentifiers {
const int kLogInId = 1;
}

namespace ConstantsForElements {
const sf::Vector2f kPositionOfLogIn = {100.0f, 100.0f};
}

namespace LogInUiConstants {
const char kBackGroundStringForUsername[] = "user name";
const sf::Color kColorForRectangleForUsername(100, 100, 100);
const size_t kSizeOfCharacterForUsername = 20;
const sf::Vector2f kPositionForUsername({0, 0});
const size_t kLimitOfCharsForUsername = 15;

const char kBackGroundStringForPassword[] = "password";
const sf::Color kColorForRectangleForPassword(100, 100, 100);
const size_t kSizeOfCharacterForPassword = 20;
const sf::Vector2f kPositionForPassword({0,
                                         0 + kSizeOfCharacterForUsername + 25});
const size_t kLimitOfCharsForPassword = 15;

const char kNameOfLogInButton[] = "Log In";
const size_t kSizeOfCharForLogInButton = 20;
const sf::Vector2f kPositionForLogInButton(
    {40, 0 + kSizeOfCharacterForUsername + kSizeOfCharacterForPassword + 50});
const sf::Color kColorForLogInButton(77, 77, 77);
const sf::Color kColorTextForLogInButton(182, 182, 182);

const char kNameOfSignInButton[] = "Sign In";
const size_t kSizeOfCharForSignInButton = 20;
const sf::Vector2f kPositionForSignInButton(
    {30, 0 + kSizeOfCharacterForUsername + kSizeOfCharacterForPassword +
             kSizeOfCharForLogInButton + 65});
const sf::Color kColorForSignInButton(77, 77, 77);
const sf::Color kColorTextForSignInButton(182, 182, 182);
}  // namespace LogInUiConstants