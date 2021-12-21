/*!
 * \file Style.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once
#include <SFML/Config.hpp>
#include <SFML/Window/WindowStyle.hpp>

namespace loki::window {

struct Style {
  static const Style NONE;
  static const Style TITLEBAR;
  static const Style RESIZE;
  static const Style CLOSE;
  static const Style FULLSCREEN;
  static const Style LETTERBOXED_ZOOM;
  static const Style INTEGER_ZOOM_RATIO;
  static const Style DEFAULT;

  sf::Uint32 value;

  Style& operator|=(Style second);
  Style operator|(Style second) const;
  [[nodiscard]] bool contains(Style flags) const;
  [[nodiscard]] sf::Uint32 toSFMLWindowStyle() const;
};

}  // namespace loki::window
