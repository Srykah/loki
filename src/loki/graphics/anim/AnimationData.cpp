/*!
 * \file AnimationData.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "AnimationData.hpp"
#include <fmt/format.h>

namespace {

std::string toPercent(float val) {
  return fmt::format("{:.2f}%", 100.f * val);
}

float fromPercent(const std::string& str) {
  return strtof(str.c_str(), nullptr) / 100.f;
}

}

namespace loki::anim {

void to_json(nlohmann::json& json, const AnimationData& data) {
  json["duration"] = data.duration;
  json["repeat"] = data.repeat;
  json["interpolation"] = data.interpolation;
  for (const auto& [time, keyframe] : data.keyframes) {
    json["keyframes"].emplace(toPercent(time), keyframe);
  }
}

void from_json(const nlohmann::json& json, AnimationData& data) {
  json.at("duration").get_to(data.duration);
  json.at("repeat").get_to(data.repeat);
  json.at("interpolation").get_to(data.interpolation);
  for (const auto& [percent, keyframe] : json.at("keyframes").items()) {
    keyframe.get_to(data.keyframes[fromPercent(percent)]);
  }
}

}
