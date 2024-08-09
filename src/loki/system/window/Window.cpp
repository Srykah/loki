#include "Window.hpp"

#include <SFML/Window/Event.hpp>

#include <loki/core/math/Rect.hpp>
#include <loki/core/math/Vector2Ops.hpp>

namespace loki::system {

void Window::create(sf::Vector2f size, std::string_view name, WindowStyle _style, bool setMinSizeAndRes) {
  style = _style;
  if (setMinSizeAndRes) {
    setMinimumSize(size);
    setInternalResolution(size);
  }
  setRenderingArea({{0, 0}, size});
  window.create(sf::VideoMode(size.x, size.y), sf::String::fromUtf8(name.begin(), name.end()),
                toSFMLWindowStyle(_style));
  updateViewport();
}

void Window::setInternalResolution(sf::Vector2f _internalResolution) {
  internalResolution = _internalResolution;
  if (isOpen()) {
    updateViewport();
  }
}

void Window::setMinimumSize(sf::Vector2f _minimumSize) {
  minimumSize = _minimumSize;
  if (isOpen()) {
    guardMinimumSize();
  }
}

void Window::setRenderingArea(sf::FloatRect&& _renderingArea) {
  renderingArea = std::move(_renderingArea);
  if (isOpen()) {
    updateViewport();
  }
}

void Window::updateViewport() {
  sf::FloatRect scaledRenderingArea = renderingArea;
  const bool styleContainsIntegerScaling = contains(style, WindowStyle::INTEGER_SCALING);
  const bool styleContainsLetterboxed = contains(style, WindowStyle::LETTERBOXED);
  if (styleContainsIntegerScaling || styleContainsLetterboxed) {
    const float viewportRatio = styleContainsIntegerScaling ? getIntegerScalingRatio() : getLetterboxedRatio();
    const sf::Vector2f scaledInternalResolution = viewportRatio * sf::Vector2f{internalResolution};
    const sf::Vector2f scaledRenderingAreaPos =
        renderingArea.getPosition() + 0.5f * (renderingArea.getSize() - scaledInternalResolution);
    scaledRenderingArea = sf::FloatRect{scaledRenderingAreaPos, scaledInternalResolution};
  }
  sf::FloatRect viewport{
      scaledRenderingArea.left / window.getSize().x,
      scaledRenderingArea.top / window.getSize().y,
      scaledRenderingArea.width / window.getSize().x,
      scaledRenderingArea.height / window.getSize().y,
  };
  sf::View view = window.getDefaultView();
  view.setViewport(viewport);
  window.setView(view);
}

bool Window::pollEvent(sf::Event& event) {
  auto res = window.pollEvent(event);

  if (event.type == sf::Event::Resized) {
    guardMinimumSize();
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

float Window::getLetterboxedRatio() {
  float renderingAreaRatio = renderingArea.width / renderingArea.height;
  float internalResolutionRatio = internalResolution.x / internalResolution.y;
  if (renderingAreaRatio >= internalResolutionRatio) {  // rendering area too wide
    return renderingArea.height / internalResolution.y;
  } else {  // rendering area too tall
    return renderingArea.width / internalResolution.x;
  }
}

float Window::getIntegerScalingRatio() {
  float letterboxedRatio = getLetterboxedRatio();
  return letterboxedRatio >= 1.f ? std::floor(letterboxedRatio) : letterboxedRatio;
}

void Window::guardMinimumSize() {
  window.setSize(core::compMax(window.getSize(), sf::Vector2u{minimumSize}));
  updateViewport();
}

void Window::close() {
  window.close();
}

}  // namespace loki::system
