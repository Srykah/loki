/*!
 * \file Window.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "Window.hpp"
#include <SFML/Window/Event.hpp>
#include <loki/core/math/Rect.hpp>
#include <loki/core/math/Vector2Ops.hpp>

namespace loki::window {

Window::Window(sf::Vector2f renderSize,
               const sf::String& title,
               Style style,
               const sf::ContextSettings& settings,
               sf::Vector2u minimumSize)
    : Window(renderSize,
             contains(style, Style::FULLSCREEN)
                 ? sf::VideoMode::getFullscreenModes()[0]
                 : sf::VideoMode(renderSize.x, renderSize.y),
             title,
             style,
             settings,
             minimumSize) {}

Window::Window(sf::Vector2f renderSize,
               sf::VideoMode mode,
               const sf::String& title,
               Style style,
               const sf::ContextSettings& settings,
               sf::Vector2u minimumSize)
    : window(mode, title, toSFMLWindowStyle(style), settings),
      renderSize(renderSize),
      minimumSize(minimumSize),
      style(style) {
  setView(sf::View{renderSize / 2.f, renderSize});
}

void Window::setView(sf::View view) {
  sf::Vector2f viewportSize{1.f, 1.f};
  if (contains(style, Style::INTEGER_ZOOM_RATIO)) {
    viewportSize = getIntegerZoomViewportSize();
  } else if (contains(style, Style::LETTERBOXED_ZOOM)) {
    viewportSize = getLetterboxedViewportSize();
  }
  sf::FloatRect viewport{sf::Vector2f{0.5f, 0.5f} - viewportSize / 2.f,
                         viewportSize};
  view.setViewport(math::compMult(viewport, view.getViewport()));
  window.setView(view);
}

void Window::setViewCenter(const sf::Vector2f& center) {
  auto view = window.getView();
  view.setCenter(center);
  window.setView(view);
}

const sf::View& Window::getDefaultView() const {
  return window.getDefaultView();
}

bool Window::pollEvent(sf::Event& event) {
  auto res = window.pollEvent(event);

  if (event.type == sf::Event::Resized) {
    guardMinimumSize();
    setView(window.getView());
    event.size.width = window.getSize().x;
    event.size.height = window.getSize().y;
  }

  return res;
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

sf::Vector2f Window::getLetterboxedViewportSize() {
  auto windowWidth = window.getSize().x;
  auto windowHeight = window.getSize().y;
  float windowRatio = float(windowWidth) / float(windowHeight);
  float renderRatio = renderSize.x / renderSize.y;

  if (windowRatio >= renderRatio) {  // window too wide
    return {(windowHeight * renderRatio) / windowWidth, 1.f};
  } else {  // window too tall
    return {1.f, (windowWidth / renderRatio) / windowHeight};
  }
}

sf::Vector2f Window::getIntegerZoomViewportSize() {
  auto windowWidth = window.getSize().x;
  auto windowHeight = window.getSize().y;
  float windowRatio = float(windowWidth) / float(windowHeight);
  float renderRatio = renderSize.x / renderSize.y;
  float integerRatio;  // actually an int

  if (windowRatio >= renderRatio) {  // window too wide
    integerRatio = std::floor(windowHeight / renderSize.y);
  } else {  // window too tall
    integerRatio = std::floor(windowWidth / renderSize.x);
  }

  return integerRatio *
         math::compDiv(renderSize, sf::Vector2{windowWidth, windowHeight});
}
void Window::guardMinimumSize() {
  window.setSize(math::compMax(window.getSize(), minimumSize));
}

}  // namespace loki::window
