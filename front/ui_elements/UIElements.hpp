#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../../AppConstants.hpp"
#include "../../back/ClientStorage.hpp"
#include "../ui_basic/Button.hpp"
#include "../ui_basic/TextBox.hpp"

class UIElement {
 public:
  virtual void Draw(sf::RenderWindow& window) = 0;
  virtual ~UIElement() = default;
};

class OnlineUIElement : public UIElement {
 public:
  virtual void Update(sf::RenderWindow& window, sf::Event& event,
                      ClientStorage& data) = 0;
};

class OfflineUIElement : public UIElement {
 public:
  virtual void Update(sf::RenderWindow& window, sf::Event& event) = 0;
};

class LogInElement : public OfflineUIElement {
 public:
  LogInElement(sf::Vector2f position, sf::Font& font);
  void Update(sf::RenderWindow& window, sf::Event& event) override;
  void Draw(sf::RenderWindow& window) override;

 private:
  TextBox user_name_;
  TextBox password_;
  TextButton<> log_in_;
  TextButton<> sign_up_;
};
