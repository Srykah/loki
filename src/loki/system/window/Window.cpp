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

void Window::create(sf::Vector2u size, const std::string& name, Style _style) {
  window.create(sf::VideoMode(size.x, size.y),
                sf::String::fromUtf8(name.begin(), name.end()),
                toSFMLWindowStyle(_style));
  setView(getDefaultView());
}

void Window::setInternalResolution(sf::Vector2u _internalResolution) {
  internalResolution = _internalResolution;
  setView(getDefaultView());
}

void Window::setMinimumSize(sf::Vector2u _minimumSize) {
  minimumSize = _minimumSize;
  guardMinimumSize();
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
  float renderRatio = float(internalResolution.x) / float(internalResolution.y);

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
  float renderRatio = float(internalResolution.x) / float(internalResolution.y);
  float integerRatio;  // actually an int

  if (windowRatio >= renderRatio) {  // window too wide
    integerRatio = float(windowHeight / internalResolution.y);
  } else {  // window too tall
    integerRatio = float(windowWidth / internalResolution.x);
  }

  return integerRatio *
         sf::Vector2f{math::compDiv(internalResolution,
                                    sf::Vector2{windowWidth, windowHeight})};
}
void Window::guardMinimumSize() {
  window.setSize(math::compMax(window.getSize(), minimumSize));
}

}  // namespace loki::window
