#pragma once

#include <SFML/System/Time.hpp>
#include <box2d/b2_world.h>

#include <loki/physics/bodies/PhysicsBodyParams.hpp>
#include <loki/physics/world/PhysicsWorldParams.hpp>

namespace loki::physics {

class PhysicsBody;

class PhysicsWorld {
 public:
  explicit PhysicsWorld(PhysicsWorldParams&& params);

  [[nodiscard]] PhysicsBody createBody(PhysicsBodyParams&& bodyParams);

  void update(sf::Time dt);

  float getPixelsToMetersRatio() const;

 private:
  PhysicsWorldParams params;
  b2World world;
};

}  // namespace loki::physics