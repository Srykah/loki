#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <box2d/b2_math.h>

namespace loki::physics {

inline b2Vec2 toB2Vec2(sf::Vector2f v) {
  return {v.x, v.y};
}
inline sf::Vector2f toSfVec2(b2Vec2 v) {
  return {v.x, v.y};
}
inline b2Vec3 toB2Vec3(const sf::Vector3f& v) {
  return {v.x, v.y, v.z};
}
inline sf::Vector3f toSfVec3(b2Vec3 v) {
  return {v.x, v.y, v.z};
}

}  // namespace loki::physics