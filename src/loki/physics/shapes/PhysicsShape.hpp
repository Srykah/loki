#pragma once

#include <box2d/box2d.h>
#include <loki/physics/shapes/PhysicsShapeParams.hpp>
#include <loki/physics/shapes/PhysicsShapeType.hpp>

namespace loki::physics {
class PhysicsBody;

class PhysicsShape {
 private:
  friend PhysicsBody;
  explicit PhysicsShape(PhysicsBody* parentBody, const PhysicsShapeParams& shapeParams, const sf::Transformable& trs);

  void clear();  // call before body destruction to avoid individual shape destruction and mass update
  
 public:
  PhysicsShape(const PhysicsShape&) = delete;
  PhysicsShape& operator=(const PhysicsShape&) = delete;
  PhysicsShape(PhysicsShape&& _other) noexcept;
  PhysicsShape& operator=(PhysicsShape&& _other) noexcept;
  ~PhysicsShape();

  void destroy(bool updateBodyMass);
  
  [[nodiscard]] PhysicsShapeType getShapeType() const;

 private:
  PhysicsBody* parentBody = nullptr;
  b2ShapeId shapeId = b2_nullShapeId;
  bool isChain = false;
};

}  // namespace loki::physics