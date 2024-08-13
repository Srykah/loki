#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
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

  void setTransformable(const sf::Transformable& transformable);
  [[nodiscard]] sf::Vector2f getPosition() const;
  [[nodiscard]] float getRotationInDegrees() const;

  void applyForce(const sf::Vector2f& force);
  void applyLinearImpulse(const sf::Vector2f& linearImpulse);

  PhysicsWorld* getWorld() const { return parentWorld; }

  void debugDraw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  PhysicsWorld* parentWorld = nullptr;
  b2Body* body = nullptr;
};

}  // namespace loki::physics