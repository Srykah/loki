/*!
 * \file Style.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once
#include <SFML/Config.hpp>

namespace loki::window {

enum class Style : sf::Uint32 {
  NONE = 0,
  TITLEBAR = 1u << 0u,
  RESIZE = 1u << 1u,
  CLOSE = 1u << 2u,
  FULLSCREEN = 1u << 3u,
  LETTERBOXED_ZOOM = 1u << 4u,
  INTEGER_ZOOM_RATIO = 1u << 5u,
  DEFAULT = TITLEBAR | RESIZE | CLOSE | LETTERBOXED_ZOOM,
};

Style operator|(Style first, Style second);
Style operator&(Style first, Style second);

}