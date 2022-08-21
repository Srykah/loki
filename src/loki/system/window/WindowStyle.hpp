#pragma once

#include <SFML/Config.hpp>
#include <SFML/Window/WindowStyle.hpp>

namespace loki::system {

enum class WindowStyle : sf::Uint32 {
  NONE = sf::Style::None,
  TITLEBAR = sf::Style::Titlebar,
  RESIZE = sf::Style::Resize,
  CLOSE = sf::Style::Close,
  FULLSCREEN = sf::Style::Fullscreen,
  SFML_MASK = sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close |
              sf::Style::Fullscreen,
  LETTERBOXED_ZOOM = 1u << 6u,
  INTEGER_ZOOM_RATIO = 1u << 7u,
  DEFAULT = sf::Style::Default | INTEGER_ZOOM_RATIO,
  DEFAULT_MODERN = sf::Style::Default | LETTERBOXED_ZOOM,
};

[[nodiscard]] constexpr sf::Uint32 to_underlying(WindowStyle style) noexcept {
  return static_cast<sf::Uint32>(style);
}

[[nodiscard]] constexpr WindowStyle operator|(WindowStyle first,
                                              WindowStyle second) noexcept {
  return static_cast<WindowStyle>(to_underlying(first) | to_underlying(second));
}

[[nodiscard]] constexpr WindowStyle operator|(WindowStyle first,
                                              sf::Uint32 second) noexcept {
  return static_cast<WindowStyle>(to_underlying(first) | second);
}

[[nodiscard]] constexpr WindowStyle operator|(sf::Uint32 first,
                                              WindowStyle second) noexcept {
  return static_cast<WindowStyle>(first | to_underlying(second));
}

inline WindowStyle& operator|=(WindowStyle& first,
                               WindowStyle second) noexcept {
  return first = first | second;
}

inline WindowStyle& operator|=(WindowStyle& first, sf::Uint32 second) noexcept {
  return first = first | second;
}

[[nodiscard]] constexpr WindowStyle operator&(WindowStyle first,
                                              WindowStyle second) noexcept {
  return static_cast<WindowStyle>(to_underlying(first) & to_underlying(second));
}

[[nodiscard]] constexpr bool contains(WindowStyle value,
                                      WindowStyle flags) noexcept {
  return (value & flags) == flags;
}

[[nodiscard]] constexpr sf::Uint32 toSFMLWindowStyle(
    WindowStyle style) noexcept {
  return to_underlying(style & WindowStyle::SFML_MASK);
}

[[nodiscard]] constexpr WindowStyle fromSMFLWindowStyle(
    sf::Uint32 sfmlStyle) noexcept {
  return static_cast<WindowStyle>(sfmlStyle) & WindowStyle::SFML_MASK;
}

}  // namespace loki::system
