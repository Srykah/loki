#include "PhysicsBodyParams.hpp"

namespace loki::physics {

b2BodyDef PhysicsBodyParams::toBodyDef() const {
  b2BodyDef bodyDef;
  bodyDef.type = static_cast<b2BodyType>(type);
  bodyDef.linearDamping = linearDamping;
  bodyDef.angularDamping = angularDamping;
  bodyDef.gravityScale = gravityScale;
  bodyDef.fixedRotation = fixedRotation;
  bodyDef.bullet = bullet;
  return bodyDef;
}

}  // namespace loki::physics