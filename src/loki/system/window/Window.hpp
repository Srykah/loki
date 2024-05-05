/*!
 * \file Window.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <loki/core/runtimeObject/BaseObject.hpp>
#include <loki/system/window/WindowStyle.hpp>

namespace loki::system {

class Window : public core::BaseObject {
 public:
  void create(sf::Vector2u size,
              std::string_view name,
              WindowStyle style = WindowStyle::DEFAULT,
              bool setMinSizeAndRes = true);
  void setInternalResolution(sf::Vector2u internalResolution);
  void setMinimumSize(sf::Vector2u minimumSize);

  void setView(sf::View view);
  void setViewCenter(const sf::Vector2f& center);
  [[nodiscard]] const sf::View& getDefaultView() const;

  bool pollEvent(sf::Event& event);
  void update(sf::Time dt);

  void clear(sf::Color color = sf::Color::Black);
  void draw(const sf::Drawable& drawable, sf::RenderStates states = sf::RenderStates());
  void display();

  [[nodiscard]] bool isOpen() const { return window.isOpen(); }
  void close();

 private:
  sf::Vector2f getLetterboxedViewportSize();
  sf::Vector2f getIntegerZoomViewportSize();
  void guardMinimumSize();

 private:
  sf::RenderWindow window;
  sf::Vector2u internalResolution;
  sf::Vector2u minimumSize;
  WindowStyle style = WindowStyle::DEFAULT;
  bool isImGuiEnabled = true;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(Window)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::core::BaseObject, loki::system::Window)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::Window)
