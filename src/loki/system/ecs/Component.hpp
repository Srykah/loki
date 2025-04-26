#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transform.hpp>

#include <loki/core/rtti/BaseObject.hpp>
#include <loki/system/ecs/Actor.hpp>
#include <loki/system/res/ResourceHandle.hpp>
#include <loki/system/res/ResourceListener.hpp>

namespace loki::system {

struct DrawOrder;
using DebugDrawDelegate = std::function<void(DrawOrder, const sf::Drawable*)>;

class Component : public core::BaseObject, public ResourceListener {
 public:
  enum class Status { CREATED, LOADING_RESOURCES, RESOURCES_LOADED, READY, DEINIT };

 public:
  ~Component() override = default;

  [[nodiscard]] Actor getActor() const;
  [[nodiscard]] Scene& getScene() const;
  [[nodiscard]] const sf::Transform& getLocalTransform() const;
  [[nodiscard]] sf::Transform getGlobalTransform() const;
  [[nodiscard]] Status getStatus() const;

  void startInit();
  void finalizeInit();

  virtual void drawDebug(const DebugDrawDelegate& debugDrawDelegate) const {}

 protected:
  virtual void onStartInit() {}
  virtual void onFinalizeInit() {}

  template <class... Ts>
  void addResources(ResourceHandle<Ts>&... handles);

 private:
  friend class ComponentRegistry;
  friend class Scene;
  void setActor(Actor actor);

  void onResourcesLoaded() override;

 private:
  Actor actor;
  Status status = Status::CREATED;

  LOKI_RTTI_CLASS_DECLARE(Component)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::core::BaseObject, loki::system::Component)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::Component)

#include "Component.hxx"
