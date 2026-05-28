#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <box2d/box2d.h>

namespace loki::physics {

inline b2Vec2 toB2Vec2(sf::Vector2f v) {
  return {v.x, v.y};
}
inline sf::Vector2f toSfVec2(b2Vec2 v) {
  return {v.x, v.y};
}
inline sf::FloatRect toSfAABB(const b2AABB& aabb) {
  return {toSfVec2(aabb.lowerBound), toSfVec2(b2AABB_Extents(aabb))};
}

}  // namespace loki::physics