/*!
 * \file AnimatedTextStyle.cpp.c
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "AnimatedTextStyle.hpp"

namespace loki::text {

AnimatedTextStyle& AnimatedTextStyle::overrideWith(
    const AnimatedTextStyle& other) {
  TextStyle::overrideWith(other);
  if (other.appear.has_value()) {
    appear.emplace(*other.appear);
  }
  if (other.idle.has_value()) {
    idle.emplace(*other.idle);
  }
  if (other.disappear.has_value()) {
    disappear.emplace(*other.disappear);
  }
  return *this;
}

AnimatedTextStyle AnimatedTextStyle::cloneAndOverrideWith(
    const AnimatedTextStyle& other) const {
  return AnimatedTextStyle(*this).overrideWith(other);
}

AnimatedTextStyle AnimatedTextStyle::fromDefaults() {
  return AnimatedTextStyle{TextStyle::fromDefaults()};
}

}  // namespace loki::text
