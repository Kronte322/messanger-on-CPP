#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

template <typename... Args>
class Button {
 public:
  Button(sf::Vector2f position, sf::Vector2f size, sf::Color color,
         std::function<void(Args...)> func,
         bool is_continuosly_pressed = false);
  virtual void Update(sf::RenderWindow& window, sf::Event& event,
                      Args&... args);
  virtual void Draw(sf::RenderWindow& window);
  virtual ~Button() = default;

 private:
  std::function<void(Args...)> func_;
  sf::Vector2f position_;
  sf::RectangleShape rectangle_;
  sf::Color color_;
  bool is_pressed_ = false;
  bool is_continuously_pressed_ = false;
};

// template <typename... Args>
// class TextButton {
//  public:
//   TextButton(sf::V);
//   void Update(sf::RenderWindow& window, sf::Event& event,
//               Args&... args) override;
//   void Draw(sf::RenderWindow& window) override;
//   ~TextButton() = default;

//  private:
//   std::function<void(Args)> func_;
//   sf::RectangleShape rectangle_;
//   bool is_pressed_ = false;
//   bool is_continuously_pressed_ = false;
// };

sf::Color FadeIn(const sf::Color& color) {
  return sf::Color(std::max(color.r - 20, 0), std::max(color.g - 20, 0),
                   std::max(color.b - 20, 0));
}

template <typename... Args>
Button<Args...>::Button(sf::Vector2f position, sf::Vector2f size,
                        sf::Color color, std::function<void(Args...)> func,
                        bool is_continuosly_pressed)
    : position_(position),
      color_(color),
      func_(func),
      is_continuously_pressed_(is_continuosly_pressed) {
  rectangle_.setSize(size);
  rectangle_.setOutlineColor(FadeIn(color_));
  rectangle_.setFillColor(color_);
  rectangle_.setOutlineThickness(5);
  rectangle_.setPosition(position_);
}

template <typename... Args>
void Button<Args...>::Update(sf::RenderWindow& window, sf::Event& event,
                             Args&... args) {
  if (event.type == sf::Event::MouseButtonPressed) {
    sf::Vector2i position_of_mouse = sf::Mouse::getPosition(window);
    if (rectangle_.getGlobalBounds().contains(
            static_cast<sf::Vector2f>(position_of_mouse))) {
      is_pressed_ = true;
      func_(args...);
    }
  } else if ((event.type == sf::Event::MouseButtonReleased) && is_pressed_) {
    is_pressed_ = false;
  }
}

template <typename... Args>
void Button<Args...>::Draw(sf::RenderWindow& window) {
  if (is_pressed_) {
    rectangle_.setFillColor(FadeIn(color_));
    rectangle_.setOutlineColor(FadeIn(FadeIn(color_)));
  } else {
    rectangle_.setFillColor(color_);
    rectangle_.setOutlineColor(FadeIn(color_));
  }
  window.draw(rectangle_);
}
