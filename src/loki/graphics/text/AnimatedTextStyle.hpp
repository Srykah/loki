#pragma once

#include <loki/graphics/anim/ShapeAnimationData.hpp>
#include <loki/graphics/styles/TextStyle.hpp>

namespace loki::graphics {

struct AnimatedTextStyle : public graphics::TextStyle {
  std::optional<graphics::ShapeAnimationData> appear;
  std::optional<graphics::ShapeAnimationData> idle;
  std::optional<graphics::ShapeAnimationData> disappear;
  sf::Time dt;

  AnimatedTextStyle& overrideWith(const AnimatedTextStyle& other);
  [[nodiscard]] AnimatedTextStyle cloneAndOverrideWith(
      const AnimatedTextStyle& other) const;

  static AnimatedTextStyle fromDefaults();
};

}  // namespace loki::graphics
