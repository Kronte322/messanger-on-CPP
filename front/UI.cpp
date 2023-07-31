#include "UI.hpp"

#include <iostream>
#include <memory>
#include <type_traits>

#include "../AppConstants.hpp"

UI::UI(sf::Font& font) : font_(font) {}

void UI::AddElement(int id, std::unique_ptr<UIElement>&& element) {
  elements_.insert(std::make_pair(id, std::move(element)));
}

void UI::DeleteElement(int id) {
  if (elements_.find(id) != elements_.end()) {
    elements_.erase(id);
  }
}

void UI::Update(sf::RenderWindow& window, sf::Event& event,
                ClientStorage& data) {
  for (auto& item : elements_) {
    if (dynamic_cast<OnlineUIElement*>(item.second.get()) != nullptr) {
      dynamic_cast<OnlineUIElement*>(item.second.get())
          ->Update(window, event, data);
    } else {
      dynamic_cast<OfflineUIElement*>(item.second.get())->Update(window, event);
    }
  }
}

void UI::Draw(sf::RenderWindow& window) {
  for (auto& item : elements_) {
    item.second->Draw(window);
  }
}
