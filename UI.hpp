#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Button.hpp"
#include "TextBox.hpp"

class UI {
 public:
  UI() = default;
  UI(const sf::Font& font);
  void SetLogInScene();
  void Update(sf::RenderWindow& window, sf::Event& event);
  void Draw(sf::RenderWindow& window);

 private:
  void ClearUi();
  sf::Font font_;
  std::vector<TextBox> text_boxes_;
  std::vector<TextButton<UI>> buttons_;
};
