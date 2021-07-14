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
  Window(sf::Vector2u renderArea,
         const sf::String& title,
         Style style = Style::DEFAULT,
         const sf::ContextSettings& settings = sf::ContextSettings(),
         sf::Vector2u minimumSize = {});
  Window(sf::Vector2u renderArea,
         sf::VideoMode mode,
         const sf::String& title,
         Style style = Style::DEFAULT,
         const sf::ContextSettings& settings = sf::ContextSettings(),
         sf::Vector2u minimumSize = {});

  void setView(sf::View view);

  bool pollEvent(sf::Event& event);

  void clear(sf::Color color = sf::Color(0, 0, 0, 255));
  void draw(const sf::Drawable& drawable, sf::RenderStates states = sf::RenderStates());
  void display();

 private:
  void setViewport();
  sf::Uint32 getWindowStyle();

 private:
  sf::RenderWindow window;
  sf::Vector2u size;
  sf::Vector2u minimumSize;
  Style style;
  void guardMinimumSize();
};

}  // namespace loki::window
