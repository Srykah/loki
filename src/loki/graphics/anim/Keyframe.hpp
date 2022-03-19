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
  enum class Component {
    NONE = -1,
    ORIGIN,
    POSITION,
    ROTATION,
    SCALE,
    COLOR,
    TEXTURE_RECT,
    COUNT  // keep last
  };

  std::optional<sf::Vector2f> origin;
  std::optional<sf::Vector2f> position;
  std::optional<float> rotation;
  std::optional<sf::Vector2f> scale;
  std::optional<sf::Color> color;
  std::optional<sf::IntRect> textureRect;
};

NLOHMANN_JSON_SERIALIZE_ENUM(Keyframe::Component,
                             {
                                 {Keyframe::Component::NONE, nullptr},
                                 {Keyframe::Component::ORIGIN, "origin"},
                                 {Keyframe::Component::POSITION, "position"},
                                 {Keyframe::Component::ROTATION, "rotation"},
                                 {Keyframe::Component::SCALE, "scale"},
                                 {Keyframe::Component::COLOR, "color"},
                                 {Keyframe::Component::TEXTURE_RECT,
                                  "textureRect"},
                             })

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Keyframe,
                                   origin,
                                   position,
                                   rotation,
                                   scale,
                                   color,
                                   textureRect)

}  // namespace loki::anim
