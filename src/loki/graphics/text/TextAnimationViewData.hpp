/*!
 * \file TextAnimationData.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <loki/graphics/anim/AnimationViewData.hpp>

namespace loki::text {

struct TextAnimationViewData : public anim::AnimationViewData {
  TextAnimationViewData(const anim::AnimationData& animationData, sf::Time dt);

  sf::Time dt;
};

}  // namespace loki::text
