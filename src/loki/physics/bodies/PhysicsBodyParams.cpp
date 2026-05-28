#include "PhysicsBodyParams.hpp"

namespace loki::physics {

b2BodyDef PhysicsBodyParams::toBodyDef() const {
  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = static_cast<b2BodyType>(type);
  bodyDef.linearDamping = linearDamping;
  bodyDef.angularDamping = angularDamping;
  bodyDef.gravityScale = gravityScale;
  bodyDef.sleepThreshold = sleepThreshold;
  bodyDef.enableSleep = enableSleep;
  bodyDef.isAwake = isAwake;
  bodyDef.fixedRotation = fixedRotation;
  bodyDef.isBullet = isBullet;
  bodyDef.isEnabled = isEnabled;
  bodyDef.allowFastRotation = allowFastRotation;
  return bodyDef;
}

}  // namespace loki::physics