/*!
 * \file Style.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */

#include "Style.hpp"

namespace loki::window {

namespace {
// intermediate value needed because static objects' init order is random
constexpr sf::Uint32 LETTERBOXED_ZOOM_VALUE = 1u << 10u;
// might as well do the same for the other one
constexpr sf::Uint32 INTEGER_ZOOM_RATIO_VALUE = 1u << 11u;
}  // namespace

const Style Style::NONE{sf::Style::None};
const Style Style::TITLEBAR{sf::Style::Titlebar};
const Style Style::RESIZE{sf::Style::Resize};
const Style Style::CLOSE{sf::Style::Close};
const Style Style::FULLSCREEN{sf::Style::Fullscreen};
const Style Style::LETTERBOXED_ZOOM{LETTERBOXED_ZOOM_VALUE};
const Style Style::INTEGER_ZOOM_RATIO{INTEGER_ZOOM_RATIO_VALUE};
const Style Style::DEFAULT{sf::Style::Default | LETTERBOXED_ZOOM_VALUE};

Style& Style::operator|=(Style second) {
  value |= second.value;
  return *this;
}

Style Style::operator|(Style second) const {
  return second |= *this;
}

bool Style::contains(Style flags) const {
  return (value & flags.value) == flags.value;
}

sf::Uint32 Style::toSFMLWindowStyle() const {
  return value & (sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close |
                  sf::Style::Fullscreen);
}

}  // namespace loki::window
