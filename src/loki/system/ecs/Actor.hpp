#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <entt/entity/entity.hpp>

namespace loki::system {

class Actor : public sf::Transformable {
 public:
  sf::Transform getGlobalTransform() const;
  sf::Vector2f getGlobalPosition() const;
  float getGlobalRotation() const;
  sf::Vector2f getGlobalScale() const;

  template <class Comp>
  Comp& getComponent() const;

 private:
  entt::entity id;
  entt::registry& registry;
  Actor* parent = nullptr;
};

}  // namespace loki::system