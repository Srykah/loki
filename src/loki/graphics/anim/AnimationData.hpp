/*!
 * \file AnimationData.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <charconv>
#include <SFML/System/Time.hpp>
#include <nlohmann/json.hpp>
#include <loki/core/math/Interpolate.hpp>

#include "Keyframe.hpp"

namespace loki::anim {

struct AnimationData {
  AnimationData();

  sf::Time duration;
  bool repeat;
  std::map<Keyframe::Component, math::InterpolationType> interpolationTypes;
  std::map<float, Keyframe> keyframes;
};

void to_json(nlohmann::json& json, const AnimationData& data);
void from_json(const nlohmann::json& json, AnimationData& data);

}  // namespace loki::anim
