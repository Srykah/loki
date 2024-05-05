#pragma once

#include <SFML/Graphics/Transform.hpp>

#include <loki/core/runtimeObject/BaseObject.hpp>

namespace loki::system {

class Actor;

class Component : public core::BaseObject {
 public:
  ~Component() override = default;

  [[nodiscard]] Actor& getActor() const;
  [[nodiscard]] const sf::Transform& getTransform() const;

 private:
  friend class ComponentRegistry;
  void setActor(Actor& actor);

 private:
  Actor* actor = nullptr;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(Component)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::core::BaseObject, loki::system::Component)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::Component)
