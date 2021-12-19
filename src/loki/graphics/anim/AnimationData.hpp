/*!
 * \file AnimationData.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once
#include <SFML/System/Time.hpp>
#include <charconv>
#include <loki/core/math/Interpolate.hpp>
#include <nlohmann/json.hpp>
#include "Keyframe.hpp"

namespace loki::anim {

struct AnimationData {
  sf::Time duration;
  bool repeat;
  common::InterpolationType interpolation;
  std::map<float, Keyframe> keyframes;
};

void to_json(nlohmann::json& json, const AnimationData& data);
void from_json(const nlohmann::json& json, AnimationData& data);

}
