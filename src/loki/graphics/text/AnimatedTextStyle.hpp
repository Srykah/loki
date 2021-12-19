/*!
 * \file AnimatedTextStyle.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <loki/graphics/styles/TextStyle.hpp>
#include "TextAnimationViewData.hpp"

namespace loki::text {

struct AnimatedTextStyle : public loki::styles::TextStyle {
  std::optional<TextAnimationViewData> appear;
  std::optional<TextAnimationViewData> animation;
  std::optional<TextAnimationViewData> disappear;

  AnimatedTextStyle& overrideWith(const AnimatedTextStyle& other);
  AnimatedTextStyle cloneAndOverrideWith(const AnimatedTextStyle& other) const;
};

}  // namespace loki::text
