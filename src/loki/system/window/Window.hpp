/*!
 * \file Window.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "Style.hpp"

namespace loki::window {

class Window {
 public:
  void create(sf::Vector2u size, const std::string& name, Style style);
  void setInternalResolution(sf::Vector2u internalResolution);
  void setMinimumSize(sf::Vector2u minimumSize);

  void setView(sf::View view);
  void setViewCenter(const sf::Vector2f& center);
  [[nodiscard]] const sf::View& getDefaultView() const;

  bool pollEvent(sf::Event& event);

  void clear(sf::Color color = sf::Color::Black);
  void draw(const sf::Drawable& drawable,
            sf::RenderStates states = sf::RenderStates());
  void display();

  [[nodiscard]] bool isOpen() const { return window.isOpen(); }
  void close() { window.close(); }

 private:
  sf::Vector2f getLetterboxedViewportSize();
  sf::Vector2f getIntegerZoomViewportSize();
  void guardMinimumSize();

 private:
  sf::RenderWindow window;
  sf::Vector2u internalResolution;
  sf::Vector2u minimumSize;
  Style style = Style::DEFAULT;
};

}  // namespace loki::window
