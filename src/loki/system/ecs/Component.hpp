#pragma once

#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Time.hpp>

#include <loki/core/runtimeObject/BaseObject.hpp>
#include <loki/system/ecs/Actor.hpp>
#include <loki/system/res/ResourceHandle.hpp>
#include <loki/system/res/ResourceListener.hpp>

namespace loki::system {

class Component : public core::BaseObject, public system::ResourceListener {
 public:
  enum class Status { CREATED, LOADING_RESOURCES, RESOURCES_LOADED, READY, DEINIT };

 public:
  ~Component() override = default;

  [[nodiscard]] Actor getActor() const;
  [[nodiscard]] const sf::Transform& getLocalTransform() const;
  [[nodiscard]] sf::Transform getGlobalTransform() const;
  [[nodiscard]] Status getStatus() const;

  void startInit();
  void finalizeInit();
  virtual void update(sf::Time dt) {}

 protected:
  virtual void onStartInit() {}
  virtual void onFinalizeInit() {}

  template <class... Ts>
  void addResources(ResourceHandle<Ts>&... handles);

 private:
  friend class ComponentRegistry;
  void setActor(Actor actor);

  void onResourcesLoaded() override;

 private:
  Actor actor;
  Status status = Status::CREATED;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(Component)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::core::BaseObject, loki::system::Component)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::Component)

#include "Component.hxx"
