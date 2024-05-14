#include "PhysicsFixtureParams.hpp"

namespace loki::physics {

b2FixtureDef PhysicsFixtureParams::toFixtureDef() const {
  b2FixtureDef fixtureDef;
  fixtureDef.friction = friction;
  fixtureDef.restitution = restitution;
  fixtureDef.restitutionThreshold = restitutionThreshold;
  fixtureDef.density = density;
  fixtureDef.isSensor = isSensor;
  fixtureDef.shape = shapeParams->getB2Shape();

  return fixtureDef;
}
}  // namespace loki::physics
