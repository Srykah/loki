/*!
 * \file Keyframe.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once
#include <loki/core/json/All.hpp>
#include <nlohmann/json.hpp>
#include <optional>

namespace loki::anim {

struct Keyframe {
  std::optional<sf::Vector2f> origin;
  std::optional<sf::Vector2f> position;
  std::optional<float> rotation;
  std::optional<sf::Vector2f> scale;
  std::optional<sf::Color> color;
  std::optional<sf::IntRect> textureRect;
};

inline void to_json(nlohmann::json& nlohmann_json_j,
                    const Keyframe& nlohmann_json_t) {
  nlohmann_json_j["origin"] = nlohmann_json_t.origin;
  nlohmann_json_j["position"] = nlohmann_json_t.position;
  nlohmann_json_j["rotation"] = nlohmann_json_t.rotation;
  nlohmann_json_j["scale"] = nlohmann_json_t.scale;
  nlohmann_json_j["color"] = nlohmann_json_t.color;
  nlohmann_json_j["textureRect"] = nlohmann_json_t.textureRect;
}

inline void from_json(const nlohmann::json& nlohmann_json_j,
                      Keyframe& nlohmann_json_t) {
#define LOKI_GET_OPTIONAL_FIELD(field)                               \
  nlohmann_json_t.field =                                            \
      nlohmann_json_j.value<decltype(nlohmann_json_t.field)>(#field, \
                                                             std::nullopt)
  LOKI_GET_OPTIONAL_FIELD(origin);
  LOKI_GET_OPTIONAL_FIELD(position);
  LOKI_GET_OPTIONAL_FIELD(rotation);
  LOKI_GET_OPTIONAL_FIELD(scale);
  LOKI_GET_OPTIONAL_FIELD(color);
  LOKI_GET_OPTIONAL_FIELD(textureRect);
#undef LOKI_GET_OPTIONAL_FIELD
}

}  // namespace loki::anim
