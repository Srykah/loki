#pragma once

#include <box2d/b2_chain_shape.h>

namespace loki::physics {
class PhysicsBody;

class ChainShape {
 private:
  PhysicsBody* parentBody = nullptr;
  b2ChainShape* chainShape = nullptr;
};

}  // namespace loki::physics