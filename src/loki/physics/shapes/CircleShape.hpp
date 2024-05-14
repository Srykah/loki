#pragma once

#include <box2d/b2_circle_shape.h>

namespace loki::physics {
class PhysicsBody;

class CircleShape {
 private:
  PhysicsBody* parentBody = nullptr;
  b2CircleShape* circleShape = nullptr;
};

}  // namespace loki::physics