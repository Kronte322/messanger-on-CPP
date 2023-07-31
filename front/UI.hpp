#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

#include "../back/ClientStorage.hpp"
#include "../front/ui_elements/UIElements.hpp"

class UI {
 public:
  UI(sf::Font& font);

  void AddElement(int id, std::unique_ptr<UIElement>&& element);

  void DeleteElement(int id);

  void Update(sf::RenderWindow& window, sf::Event& event, ClientStorage& data);

  void Draw(sf::RenderWindow& window);

 private:
  sf::Font& font_;
  std::unordered_map<int, std::unique_ptr<UIElement>> elements_;
};
