#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

#include "AppConstants.hpp"

template <typename... Args>
class Button {
 public:
  Button(sf::Vector2f position, sf::Vector2f size, sf::Color color,
         std::function<void(Args&...)> func,
         bool is_continuosly_pressed = false);
  virtual void Update(sf::RenderWindow& window, sf::Event& event,
                      Args&... args);
  virtual void Draw(sf::RenderWindow& window);
  virtual ~Button() = default;

 private:
  static sf::Color FadeIn(const sf::Color& color) {
    return sf::Color(std::max(color.r - 20, 0), std::max(color.g - 20, 0),
                     std::max(color.b - 20, 0));
  }
  std::function<void(Args&...)> func_;
  sf::Vector2f position_;
  sf::RectangleShape rectangle_;
  sf::Color color_;
  bool is_pressed_ = false;
  bool is_continuously_pressed_ = false;
};

template <typename... Args>
class TextButton : public Button<Args...> {
 public:
  TextButton(const sf::String& str, const sf::Font& font, size_t character_size,
             sf::Vector2f position, sf::Color color_for_rectangle,
             sf::Color color_for_button,
             const std::function<void(Args&...)>& func,
             bool is_continuosly_pressed = false);
  void Draw(sf::RenderWindow& window) override;
  ~TextButton() = default;

 private:
  sf::Text text_;
  sf::Color color_for_text_;
  sf::String str_;
};

template <typename... Args>
TextButton<Args...>::TextButton(const sf::String& str, const sf::Font& font,
                                size_t character_size, sf::Vector2f position,
                                sf::Color color_for_rectangle,
                                sf::Color color_for_text,
                                const std::function<void(Args&...)>& func,
                                bool is_continuosly_pressed)
    : Button<Args...>(
          position,
          sf::Vector2f(character_size * str.getSize(), character_size),
          color_for_rectangle, func, is_continuosly_pressed) {
  str_ = str;
  color_for_text_ = color_for_text;
  text_.setFont(font);
  text_.setCharacterSize(character_size);
  text_.setPosition(position);
  text_.setFillColor(color_for_text_);
  text_.setStyle(sf::Text::Bold);
  text_.setString(str_);
}

template <typename... Args>
void TextButton<Args...>::Draw(sf::RenderWindow& window) {
  Button<Args...>::Draw(window);
  window.draw(text_);
}

template <typename... Args>
Button<Args...>::Button(sf::Vector2f position, sf::Vector2f size,
                        sf::Color color, std::function<void(Args&...)> func,
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
