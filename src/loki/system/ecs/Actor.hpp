#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <entt/entity/registry.hpp>

#include <loki/system/scene/SceneNode.hpp>

namespace loki::system {

class Actor : public SceneNode {
 public:
  Actor* getParentActor() const;

  template <class Comp>
  Comp& getComponent() const;

 private:
  friend class ActorManager;
  explicit Actor(entt::registry& registry, Actor* parent = nullptr);

  entt::entity id;
  entt::registry& registry;
  bool isRoot = true;
};

}  // namespace loki::system