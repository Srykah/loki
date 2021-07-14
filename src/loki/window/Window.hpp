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
  Window(sf::Vector2f renderSize,
         const sf::String& title,
         Style style = Style::DEFAULT,
         const sf::ContextSettings& settings = sf::ContextSettings(),
         sf::Vector2u minimumSize = {});
  Window(sf::Vector2f renderSize,
         sf::VideoMode mode,
         const sf::String& title,
         Style style = Style::DEFAULT,
         const sf::ContextSettings& settings = sf::ContextSettings(),
         sf::Vector2u minimumSize = {});

  void setView(sf::View view);
  void setViewCenter(const sf::Vector2f& center);
  [[nodiscard]] const sf::View& getDefaultView() const;

  bool pollEvent(sf::Event& event);

  void clear(sf::Color color = sf::Color::Black);
  void draw(const sf::Drawable& drawable, sf::RenderStates states = sf::RenderStates());
  void display();

 private:
  sf::Vector2f getLetterboxedViewportSize();
  sf::Vector2f getIntegerZoomViewportSize();
  void guardMinimumSize();

 private:
  sf::RenderWindow window;
  sf::Vector2f renderSize;
  sf::Vector2u minimumSize;
  Style style;
};

}  // namespace loki::window
