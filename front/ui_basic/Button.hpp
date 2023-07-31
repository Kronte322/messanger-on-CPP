#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

#include "../../AppConstants.hpp"

template <typename... Args>
class Button {
 public:
  Button(std::function<void(Args...)> func,
         sf::Vector2f position = {0.0f, 0.0f},
         sf::Vector2f size = {100.0f, 100.0f},
         sf::Color color = sf::Color(40, 65, 134),
         bool is_continuosly_pressed = false);

  void SetSize(const sf::Vector2f& size);
  virtual void Update(sf::RenderWindow& window, sf::Event& event, Args... args);
  virtual void Draw(sf::RenderWindow& window);
  virtual ~Button() = default;

 private:
  static sf::Color FadeIn(const sf::Color& color) {
    return sf::Color(std::max(color.r - 20, 0), std::max(color.g - 20, 0),
                     std::max(color.b - 20, 0));
  }
  std::function<void(Args...)> func_;
  sf::RectangleShape rectangle_;
  sf::Color color_;
  bool is_pressed_ = false;
  bool is_continuously_pressed_ = false;
};

template <typename... Args>
class TextButton : public Button<Args...> {
 public:
  TextButton(const sf::Font& font, const std::function<void(Args...)>& func,
             bool is_continuosly_pressed = false,
             const sf::String& str = "Button",
             sf::Vector2f position = {0.0f, 0.0f}, size_t character_size = 20,
             sf::Color color_for_rectangle = sf::Color(40, 65, 134),
             sf::Color color_for_text = sf::Color(255, 255, 255));
  void Draw(sf::RenderWindow& window) override;
  ~TextButton() = default;

 private:
  sf::Text text_;
  sf::String str_;
};

template <typename... Args>
TextButton<Args...>::TextButton(const sf::Font& font,
                                const std::function<void(Args...)>& func,
                                bool is_continuosly_pressed,
                                const sf::String& str, sf::Vector2f position,
                                size_t character_size,
                                sf::Color color_for_rectangle,
                                sf::Color color_for_text)
    : Button<Args...>(
          func, position,
          sf::Vector2f(character_size * str.getSize(), character_size),
          color_for_rectangle, is_continuosly_pressed) {
  str_ = str;
  text_.setFont(font);
  text_.setCharacterSize(character_size);
  text_.setPosition(position);
  text_.setFillColor(color_for_text);
  text_.setStyle(sf::Text::Bold);
  text_.setString(str_);
  this->SetSize(
      {text_.getGlobalBounds().width, text_.getGlobalBounds().height});
}

template <typename... Args>
void TextButton<Args...>::Draw(sf::RenderWindow& window) {
  Button<Args...>::Draw(window);
  window.draw(text_);
}

template <typename... Args>
Button<Args...>::Button(std::function<void(Args...)> func,
                        sf::Vector2f position, sf::Vector2f size,
                        sf::Color color, bool is_continuosly_pressed)
    : color_(color),
      func_(func),
      is_continuously_pressed_(is_continuosly_pressed) {
  rectangle_.setPosition(position);
  rectangle_.setSize(size);
  rectangle_.setFillColor(color_);
  rectangle_.setOutlineThickness(5);
  rectangle_.setOutlineColor(FadeIn(color_));
}

template <typename... Args>
void Button<Args...>::Update(sf::RenderWindow& window, sf::Event& event,
                             Args... args) {
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

template <typename... Args>
void Button<Args...>::SetSize(const sf::Vector2f& size) {
  rectangle_.setSize(size);
}