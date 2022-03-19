/*!
 * \file TextAnimationViewData.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TextAnimationViewData.hpp"

namespace loki::text {

TextAnimationViewData::TextAnimationViewData(
    const anim::AnimationData& animationData,
    sf::Time dt)
    : AnimationViewData(animationData), dt(dt) {}

}  // namespace loki::text
