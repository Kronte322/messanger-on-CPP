#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>

class UiClasses {
 public:
  virtual void Update(sf::RenderWindow& window, sf::Event& event) = 0;
  virtual void Draw(sf::RenderWindow& window) = 0;
  virtual ~UiClasses() = 0;

 private:
};

class TextBox : public UiClasses {
 public:
  TextBox(sf::Font& font_, std::string back_ground_text,
          sf::Color color_for_text, sf::Color color_for_rectangle,
          int size_of_character, sf::Vector2f position,
          sf::Vector2f size_of_box, size_t limit_of_chars,
          bool is_password = false, bool is_line_breakable = true);

  void Update(sf::RenderWindow& window, sf::Event& event) override;

  void Draw(sf::RenderWindow& window) override;

  ~TextBox() = default;

 private:
  static std::unordered_map<char32_t, std::function<void(TextBox&)>> actions_;

  void AddElement(sf::Uint32 symbol);

  void CheckIsLastActive();

  static void RemoveLastElement(TextBox& text_box);

  static void AddLineBreak(TextBox& text_box);
  sf::Font& font_;
  sf::Text text_;
  sf::String entered_text_;
  sf::Text back_ground_text_;
  sf::String back_text_;
  sf::Color color_for_text_;
  sf::Color color_for_rectangle_;
  sf::RectangleShape rectangle_;
  bool is_active_ = false;
  bool is_on_the_screen_ = true;
  bool is_back_ground_message_active_ = true;
  int size_of_character_ = 20;
  sf::Vector2f position_ = {0, 0};
  sf::Vector2f size_of_box_ = {0, 0};
  size_t limit_of_chars_ = 0;
  bool is_password_ = false;
  bool is_line_breakable_ = true;
  size_t counter_of_frames_ = 0;
  bool sign_for_last_ = false;
};
