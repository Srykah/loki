#pragma once

#include <SFML/System/Vector2.hpp>
#include <box2d/b2_body.h>

#include <loki/physics/shapes/PhysicsFixtureParams.hpp>

namespace loki::physics {
class PhysicsWorld;

class PhysicsBody {
 public:
  PhysicsBody() = default;
  explicit PhysicsBody(b2Body* body, PhysicsWorld* parentWorld);

  void createFixture(PhysicsFixtureParams&& shapeParams);

  [[nodiscard]] sf::Vector2f getPosition() const;
  [[nodiscard]] float getRotationInDegrees() const;

 private:
  PhysicsWorld* parentWorld = nullptr;
  b2Body* body = nullptr;
};

}  // namespace loki::physics