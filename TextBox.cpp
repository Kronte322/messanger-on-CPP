#include "TextBox.hpp"

#include <algorithm>
#include <iostream>

UiClasses::~UiClasses() = default;

size_t Rfind(const sf::String& str, char symbol) {
  size_t position = 0;
  for (size_t i = 0; i < str.getSize(); ++i) {
    if (str[i] == symbol) {
      position = i + 1;
    }
  }
  return position;
}

void TextBox::CheckIsLastActive() {
  if (sign_for_last_) {
    sign_for_last_ = false;
    counter_of_frames_ = 0;
    if (!entered_text_.isEmpty()) {
      entered_text_.erase(entered_text_.getSize() - 1);
    }
  }
}

void TextBox::RemoveLastElement(TextBox& text_box) {
  if (!text_box.entered_text_.isEmpty()) {
    text_box.CheckIsLastActive();
    if (text_box.entered_text_[text_box.entered_text_.getSize() - 1] == '\n') {
      text_box.rectangle_.setSize(
          {text_box.rectangle_.getSize().x,
           text_box.rectangle_.getSize().y -
               static_cast<float>(text_box.size_of_character_ * 1.5)});
    }
    text_box.entered_text_.erase(text_box.entered_text_.getSize() - 1);
  }
}

void TextBox::AddLineBreak(TextBox& text_box) {
  if (text_box.is_line_breakable_) {
    text_box.CheckIsLastActive();
    text_box.entered_text_ += '\n';
    text_box.rectangle_.setSize(
        {text_box.rectangle_.getSize().x,
         text_box.rectangle_.getSize().y +
             static_cast<float>(text_box.size_of_character_ * 1.5)});
  }
}

void TextBox::AddElement(sf::Uint32 symbol) {
  CheckIsLastActive();
  entered_text_ += symbol;
  if (entered_text_.getSize() - Rfind(entered_text_, '\n') > limit_of_chars_) {
    AddLineBreak(*this);
  }
}

std::unordered_map<char32_t, std::function<void(TextBox&)>> TextBox::actions_ =
    {std::make_pair('\b', TextBox::RemoveLastElement),
     std::make_pair('\r', TextBox::AddLineBreak)};

TextBox::TextBox(sf::Font& font, std::string back_ground_text,
                 sf::Color color_for_text, sf::Color color_for_rectangle,
                 int size_of_character, sf::Vector2f position,
                 sf::Vector2f size_of_box, size_t limit_of_chars,
                 bool is_password, bool is_line_breakable)
    : font_(font),
      back_text_(back_ground_text),
      color_for_text_(color_for_text),
      color_for_rectangle_(color_for_rectangle),
      size_of_character_(size_of_character),
      position_(position),
      size_of_box_(size_of_box),
      limit_of_chars_(limit_of_chars),
      is_password_(is_password),
      is_line_breakable_(is_line_breakable) {
  rectangle_.setSize(
      {static_cast<float>((limit_of_chars_ + 1) * size_of_character_),
       static_cast<float>(size_of_character_ + 10)});
  rectangle_.setOutlineColor({100, 100, 100});
  rectangle_.setFillColor({80, 80, 80});
  rectangle_.setOutlineThickness(5);
  rectangle_.setPosition(position_);

  text_.setFont(font_);
  text_.setCharacterSize(size_of_character_);
  text_.setPosition({position_.x + size_of_character_ * 0.25f, position_.y});
  text_.setFillColor(color_for_text_);
  text_.setStyle(sf::Text::Bold);

  back_ground_text_.setFont(font_);
  back_ground_text_.setCharacterSize(size_of_character_);
  back_ground_text_.setPosition(
      {position_.x + size_of_character_ * 0.25f, position_.y});
  back_ground_text_.setFillColor(color_for_text_);
  back_ground_text_.setStyle(sf::Text::Bold);

  back_ground_text_.setString(back_text_);
}

void TextBox::Update(sf::RenderWindow& window, sf::Event& event) {
  if (event.type == sf::Event::MouseButtonPressed) {
    sf::Vector2i position_of_mouse = sf::Mouse::getPosition(window);
    if (is_active_ && !rectangle_.getGlobalBounds().contains(
                          static_cast<sf::Vector2f>(position_of_mouse))) {
      is_active_ = false;
      CheckIsLastActive();
    } else if (!is_active_ &&
               rectangle_.getGlobalBounds().contains(
                   static_cast<sf::Vector2f>(position_of_mouse))) {
      is_active_ = true;
    }
  } else if (is_active_) {
    if (event.type == sf::Event::TextEntered) {
      if (!actions_.contains(event.text.unicode)) {
        AddElement(event.text.unicode);
      } else {
        actions_[event.text.unicode](*this);
      }
    }
  }
  if (!entered_text_.isEmpty()) {
    is_back_ground_message_active_ = false;
  } else {
    is_back_ground_message_active_ = true;
  }
}

void TextBox::Draw(sf::RenderWindow& window) {
  if (is_active_ && !is_back_ground_message_active_) {
    if (counter_of_frames_ / 30 == 1) {
      if (sign_for_last_) {
        entered_text_.erase(entered_text_.getSize() - 1);
        sign_for_last_ = false;
      } else {
        entered_text_ += '|';
        sign_for_last_ = true;
      }
      counter_of_frames_ = 0;
    } else {
      ++counter_of_frames_;
    }
  }
  if (is_password_) {
    text_.setString(std::string(entered_text_.getSize(), '*'));
  } else {
    text_.setString(entered_text_);
  }
  if (is_on_the_screen_) {
    window.draw(rectangle_);
    if (is_back_ground_message_active_) {
      window.draw(back_ground_text_);
    }
    window.draw(text_);
  }
}
