#pragma once

#include <SFML/System/Time.hpp>
#include <box2d/box2d.h>

#include <loki/physics/bodies/PhysicsBodyParams.hpp>
#include <loki/physics/world/PhysicsWorldParams.hpp>

namespace loki::physics {

class PhysicsBody;

class PhysicsWorld {
 public:
  explicit PhysicsWorld(PhysicsWorldParams&& params);
  ~PhysicsWorld();

  [[nodiscard]] PhysicsBody createBody(PhysicsBodyParams&& bodyParams);

  void update(sf::Time dt);

  float getPixelsToMetersRatio() const;
  b2WorldId getWorldId() const { return worldId; }

 private:
  PhysicsWorldParams params;
  b2WorldId worldId;
};

}  // namespace loki::physics