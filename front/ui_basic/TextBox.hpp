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
  TextBox(sf::Font& font, sf::Vector2f position = sf::Vector2f(0, 0),
          int size_of_character = 20, size_t limit_of_chars = 20,
          std::string back_ground_text = "Enter Text",
          sf::Color color_for_text = sf::Color(255, 255, 255),
          sf::Color color_for_rectangle = sf::Color(40, 65, 134),
          bool is_password = false, bool is_line_breakable = true);

  void Update(sf::RenderWindow& window, sf::Event& event) override;

  void Draw(sf::RenderWindow& window) override;

  std::string GetEnteredText() const;

  ~TextBox() = default;

 private:
  static std::unordered_map<char32_t, std::function<void(TextBox&)>> actions_;

  void AddElement(sf::Uint32 symbol);

  void CheckIsLastActive();

  static void RemoveLastElement(TextBox& text_box);

  static void AddLineBreak(TextBox& text_box);

  sf::Font& font_;
  sf::Text text_;
  sf::Text back_ground_text_;
  sf::String entered_text_;
  sf::String back_text_;
  sf::RectangleShape rectangle_;
  sf::Vector2f position_;
  size_t size_of_character_ = 0;
  size_t limit_of_chars_ = 0;
  size_t counter_of_frames_ = 0;
  bool is_active_ = false;
  bool is_on_the_screen_ = true;
  bool is_back_ground_message_active_ = true;
  bool is_password_ = false;
  bool is_line_breakable_ = true;
  bool sign_for_last_ = false;
};
