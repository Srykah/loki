/*!
 * \file Style.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once
#include <SFML/Config.hpp>
#include <SFML/Window/WindowStyle.hpp>

namespace loki::window {

enum class Style : sf::Uint32 {
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

[[nodiscard]] constexpr sf::Uint32 to_underlying(Style style) noexcept {
  return static_cast<sf::Uint32>(style);
}

[[nodiscard]] constexpr Style operator|(Style first, Style second) noexcept {
  return static_cast<Style>(to_underlying(first) | to_underlying(second));
}

[[nodiscard]] constexpr Style operator|(Style first,
                                        sf::Uint32 second) noexcept {
  return static_cast<Style>(to_underlying(first) | second);
}

[[nodiscard]] constexpr Style operator|(sf::Uint32 first,
                                        Style second) noexcept {
  return static_cast<Style>(first | to_underlying(second));
}

inline Style& operator|=(Style& first, Style second) noexcept {
  return first = first | second;
}

inline Style& operator|=(Style& first, sf::Uint32 second) noexcept {
  return first = first | second;
}

[[nodiscard]] constexpr Style operator&(Style first, Style second) noexcept {
  return static_cast<Style>(to_underlying(first) & to_underlying(second));
}

[[nodiscard]] constexpr bool contains(Style value, Style flags) noexcept {
  return (value & flags) == flags;
}

[[nodiscard]] constexpr sf::Uint32 toSFMLWindowStyle(Style style) noexcept {
  return to_underlying(style & Style::SFML_MASK);
}

[[nodiscard]] constexpr Style fromSMFLWindowStyle(
    sf::Uint32 sfmlStyle) noexcept {
  return static_cast<Style>(sfmlStyle) & Style::SFML_MASK;
}

}  // namespace loki::window
