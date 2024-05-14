#pragma once

#include <box2d/b2_polygon_shape.h>

namespace loki::physics {
class PhysicsBody;

class PolygonShape {
 private:
  PhysicsBody* parentBody = nullptr;
  b2PolygonShape* polygonShape = nullptr;
};

}  // namespace loki::physics