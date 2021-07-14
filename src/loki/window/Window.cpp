/*!
 * \file Window.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "Window.hpp"
#include <SFML/Window/Event.hpp>

namespace loki::window {

Window::Window(sf::Vector2u renderArea,
               const sf::String& title,
               Style style,
               const sf::ContextSettings& settings,
               sf::Vector2u minimumSize)
    : Window(renderArea,
             style.contains(Style::FULLSCREEN)
                 ? sf::VideoMode::getFullscreenModes()[0]
                 : sf::VideoMode(renderArea.x, renderArea.y),
             title,
             style,
             settings,
             minimumSize) {}

Window::Window(sf::Vector2u renderArea,
               sf::VideoMode mode,
               const sf::String& title,
               Style style,
               const sf::ContextSettings& settings,
               sf::Vector2u minimumSize)
    : size(renderArea), minimumSize(minimumSize), style(style) {
  window.create(sf::VideoMode(renderArea.x, renderArea.y), title,
                style.toSFMLWindowStyle(), settings);
  setViewport();
}

bool Window::pollEvent(sf::Event& event) {
  auto res = window.pollEvent(event);

  if (event.type == sf::Event::Resized) {
    guardMinimumSize();
    setViewport();
  }

  return res;
}

void Window::setViewport() {
  float windowRatio = float(window.getSize().x) / float(window.getSize().y);
  float internalRatio = float(size.x) / float(size.y);
  sf::View view{window.getView()};
  sf::Vector2f viewportSize{1.f, 1.f};
  if (bool(style & Style::LETTERBOXED_ZOOM)) {
    if (windowRatio >= internalRatio) {  // window too wide
      viewportSize = {window.getSize().y * internalRatio, 1.f};
    } else {  // window too tall
      viewportSize = {1.f, window.getSize().x / internalRatio};
    }
  } else if (bool(style & Style::INTEGER_ZOOM_RATIO)) {
    unsigned int integerRatio;
    if (windowRatio >= internalRatio) {  // window too wide
      integerRatio = window.getSize().y / size.y;
    } else {  // window too tall
      integerRatio = window.getSize().x / size.x;
    }
    viewportSize = {float(size.x * integerRatio) / float(window.getSize().x),
                    float(size.y * integerRatio) / float(window.getSize().y)};
  }
  view.setViewport(
      {sf::Vector2f{0.5f, 0.5f} - viewportSize / 2.f, viewportSize});
  window.setView(view);
}

sf::Uint32 Window::getWindowStyle() {
  return static_cast<sf::Uint32>(style) & ((1u << 4u) - 1u);
}

void Window::guardMinimumSize() {
  window.setSize(sf::Vector2u{std::max(window.getSize().x, minimumSize.x),
                              std::max(window.getSize().y, minimumSize.y)});
}

void Window::setView(sf::View view) {
  window.setView(view);
}

void Window::clear(sf::Color color) {
  window.clear(color);
}

void Window::draw(const sf::Drawable& drawable, sf::RenderStates states) {
  window.draw(drawable, states);
}

void Window::display() {
  window.display();
}

}  // namespace loki::window
