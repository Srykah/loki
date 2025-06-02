#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transform.hpp>

#include <loki/core/rtti/BaseObject.hpp>
#include <loki/core/rtti/rttiMacros.hpp>
#include <loki/system/ecs/Actor.hpp>
#include <loki/system/ecs/LifeCycleStep.hpp>
#include <loki/system/res/ResourceHandle.hpp>
#include <loki/system/res/ResourceListener.hpp>
#include <loki/system/scheduler/Updatable.hpp>

namespace loki::system {

struct DrawOrder;
using DebugDrawDelegate = std::function<void(DrawOrder, const sf::Drawable*)>;

class Component : public core::BaseObject, public ResourceListener, public Updatable, public WithLifeCycle {
 public:
  ~Component() override = default;

  [[nodiscard]] Actor getActor() const;
  [[nodiscard]] Scene& getScene() const;
  [[nodiscard]] const sf::Transform& getLocalTransform() const;
  [[nodiscard]] sf::Transform getGlobalTransform() const;

  virtual void drawDebug(const DebugDrawDelegate& debugDrawDelegate) const {}

 protected:
  template <class... Ts>
  void addResources(ResourceHandle<Ts>&... handles);

 private:
  friend class ComponentRegistry;
  friend class Scene;
  void setActor(Actor actor);

 private:
  Actor actor;

  LOKI_RTTI_CLASS_DECLARE(Component)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_RTTI(loki::system::Component)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::Component)

#include "Component.hxx"

#define LOKI_REFLECTION_COMPONENT_BEGIN(Comp) LOKI_REFLECTION_CLASS_BEGIN_CHILD(Comp, loki::system::Component)