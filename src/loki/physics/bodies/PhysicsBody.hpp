#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <box2d/box2d.h>
#include <loki/physics/bodies/PhysicsBodyParams.hpp>
#include <loki/physics/shapes/PhysicsShape.hpp>

namespace loki::physics {

class PhysicsBody {
 private:
  friend class PhysicsWorld;
  explicit PhysicsBody(const PhysicsBodyParams& bodyParams, PhysicsWorld* parentWorld);

 public:
  PhysicsBody() = default;
  ~PhysicsBody();

  PhysicsShape& createShape(const PhysicsShapeParams& shapeParams, const sf::Transformable& trs = {});

  void setTransformable(const sf::Transformable& transformable);
  [[nodiscard]] sf::Vector2f getPosition() const;
  [[nodiscard]] sf::Angle getRotation() const;

  void applyForce(const sf::Vector2f& force);
  void applyLinearImpulse(const sf::Vector2f& linearImpulse);

  PhysicsWorld* getWorld() const { return parentWorld; }
  b2BodyId getBodyId() const { return bodyId; }
  sf::FloatRect getBoundingBox() const;

  PhysicsWorld* parentWorld = nullptr;
  b2BodyId bodyId = b2_nullBodyId;
  std::vector<PhysicsShape> shapes;
};

}  // namespace loki::physics