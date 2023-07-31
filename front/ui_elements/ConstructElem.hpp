#include <SFML/Graphics.hpp>
#include <memory>

#include "../../AppConstants.hpp"
#include "../ui_elements/UIElements.hpp"

template <int id>
std::unique_ptr<UIElement> GetElement(sf::Font& font) {}

template <>
std::unique_ptr<UIElement> GetElement<ElementsIdentifiers::kLogInId>(
    sf::Font& font) {
  return std::unique_ptr<UIElement>(
      new LogInElement(ConstantsForElements::kPositionOfLogIn, font));
}
