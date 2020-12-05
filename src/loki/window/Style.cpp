/*!
 * \file Style.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */

#include "Style.hpp"
namespace loki::window {

Style operator|(Style first, Style second) {
  return Style{static_cast<sf::Uint32>(first) |
               static_cast<sf::Uint32>(second)};
}

Style operator&(Style first, Style second) {
  return Style{static_cast<sf::Uint32>(first) &
               static_cast<sf::Uint32>(second)};
}

}  // namespace loki::window