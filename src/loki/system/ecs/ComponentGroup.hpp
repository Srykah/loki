#pragma once

#include <SFML/System/Time.hpp>
#include <entt/entity/registry.hpp>

namespace loki::system {

class ComponentGroupBase {
 public:
  virtual ~ComponentGroupBase() = default;

  virtual void update(sf::Time delta) = 0;
};

template <class Comp>
class ComponentGroup : public ComponentGroupBase {
 public:
  explicit ComponentGroup(entt::registry& registry);
  ~ComponentGroup() override = default;

  void update(sf::Time delta) override;

 private:
  entt::registry& registry;
  // decltype(entt::registry{}.group<Comp>()) group;
};

}  // namespace loki::system

#include "ComponentGroup.hxx"
