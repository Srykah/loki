#include "Window.hpp"

#include <SFML/Window/Event.hpp>

#include <loki/core/math/Rect.hpp>
#include <loki/core/math/Vector2Ops.hpp>

namespace loki::system {

void Window::create(sf::Vector2u size, std::string_view name, WindowStyle _style, bool setMinSizeAndRes) {
  style = _style;
  if (setMinSizeAndRes) {
    setMinimumSize(size);
    setInternalResolution(size);
  }
  setRenderingArea({{0, 0}, size});
  window.create(sf::VideoMode{sf::Vector2u{size}}, sf::String::fromUtf8(name.begin(), name.end()),
                toSFMLWindowStyle(_style));
  updateViewport();
}

void Window::setInternalResolution(sf::Vector2u _internalResolution) {
  internalResolution = _internalResolution;
  if (isOpen()) {
    updateViewport();
  }
}

void Window::setMinimumSize(sf::Vector2u _minimumSize) {
  minimumSize = _minimumSize;
  if (isOpen()) {
    guardMinimumSize();
  }
}

void Window::setRenderingArea(sf::Rect<unsigned int>&& _renderingArea) {
  renderingArea = std::move(_renderingArea);
  if (isOpen()) {
    updateViewport();
  }
}

void Window::updateViewport() {
  sf::FloatRect scaledRenderingArea{renderingArea};
  const bool styleContainsIntegerScaling = contains(style, WindowStyle::INTEGER_SCALING);
  const bool styleContainsLetterboxed = contains(style, WindowStyle::LETTERBOXED);
  if (styleContainsIntegerScaling || styleContainsLetterboxed) {
    const float viewportRatio = styleContainsIntegerScaling ? getIntegerScalingRatio() : getLetterboxedRatio();
    const sf::Vector2f scaledInternalResolution = viewportRatio * sf::Vector2f{internalResolution};
    const sf::Vector2f scaledRenderingAreaPos =
        sf::Vector2f{renderingArea.position} + 0.5f * (sf::Vector2f{renderingArea.size} - scaledInternalResolution);
    scaledRenderingArea = sf::FloatRect{scaledRenderingAreaPos, scaledInternalResolution};
  }
  sf::FloatRect viewport{core::compDiv(scaledRenderingArea.position, window.getSize()),
                         core::compDiv(scaledRenderingArea.size, window.getSize())};
  sf::View view = window.getDefaultView();
  view.setViewport(viewport);
  window.setView(view);
}

std::optional<sf::Event> Window::pollEvent() {
  auto res = window.pollEvent();

  if (auto* resized = res ? res->getIf<sf::Event::Resized>() : nullptr) {
    guardMinimumSize();
    auto resizedCopy = *resized;
    resizedCopy.size = window.getSize();
    return resizedCopy;
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
  float renderingAreaRatio = static_cast<float>(renderingArea.size.x) / static_cast<float>(renderingArea.size.y);
  float internalResolutionRatio = static_cast<float>(internalResolution.x) / static_cast<float>(internalResolution.y);
  if (renderingAreaRatio >= internalResolutionRatio) {  // rendering area too wide
    return static_cast<float>(renderingArea.size.y) / static_cast<float>(internalResolution.y);
  } else {  // rendering area too tall
    return static_cast<float>(renderingArea.size.x) / static_cast<float>(internalResolution.x);
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
