/*!
 * \file AnimatedTextStyle.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <loki/graphics/anim/ShapeAnimationData.hpp>
#include <loki/graphics/styles/TextStyle.hpp>

namespace loki::text {

struct AnimatedTextStyle : public styles::TextStyle {
  std::optional<anim::ShapeAnimationData> appear;
  std::optional<anim::ShapeAnimationData> idle;
  std::optional<anim::ShapeAnimationData> disappear;
  sf::Time dt;

  AnimatedTextStyle& overrideWith(const AnimatedTextStyle& other);
  [[nodiscard]] AnimatedTextStyle cloneAndOverrideWith(
      const AnimatedTextStyle& other) const;

  static AnimatedTextStyle fromDefaults();
};

}  // namespace loki::text
