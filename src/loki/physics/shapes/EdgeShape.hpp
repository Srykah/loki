#pragma once

#include <box2d/b2_edge_shape.h>

namespace loki::physics {
class PhysicsBody;

class EdgeShape {
 private:
  PhysicsBody* parentBody = nullptr;
  b2EdgeShape* edgeShape = nullptr;
};

}  // namespace loki::physics