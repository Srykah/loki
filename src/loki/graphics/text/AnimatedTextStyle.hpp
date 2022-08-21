#pragma once

#include <loki/graphics/anim/ShapeAnimationData.hpp>
#include <loki/graphics/styles/TextStyle.hpp>

namespace loki::gfx {

struct AnimatedTextStyle : public gfx::TextStyle {
  std::optional<gfx::ShapeAnimationData> appear;
  std::optional<gfx::ShapeAnimationData> idle;
  std::optional<gfx::ShapeAnimationData> disappear;
  sf::Time dt;

  AnimatedTextStyle& overrideWith(const AnimatedTextStyle& other);
  [[nodiscard]] AnimatedTextStyle cloneAndOverrideWith(
      const AnimatedTextStyle& other) const;

  static AnimatedTextStyle fromDefaults();
};

}  // namespace loki::text
