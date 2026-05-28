#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <loki/system/window/WindowStyle.hpp>

namespace loki::system {

class Window {
 public:
  void create(sf::Vector2u size,
              std::string_view name,
              WindowStyle style = WindowStyle::DEFAULT,
              bool setMinSizeAndRes = true);
  void setInternalResolution(sf::Vector2u internalResolution);
  void setMinimumSize(sf::Vector2u minimumSize);
  void setRenderingArea(sf::Rect<unsigned int>&& renderingArea);

  std::optional<sf::Event> pollEvent();

  void clear(sf::Color color = sf::Color::Black);
  void draw(const sf::Drawable& drawable, sf::RenderStates states = sf::RenderStates());
  void display();

  [[nodiscard]] bool isOpen() const { return window.isOpen(); }
  void close();

  sf::RenderWindow& getRenderWindow() { return window; }

 private:
  float getLetterboxedRatio();
  float getIntegerScalingRatio();
  void guardMinimumSize();
  void updateViewport();

 private:
  sf::RenderWindow window;
  WindowStyle style = WindowStyle::DEFAULT;
  sf::Vector2u internalResolution;
  sf::Vector2u minimumSize;
  sf::Rect<unsigned int> renderingArea;
};

}  // namespace loki::system
