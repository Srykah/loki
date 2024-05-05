#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <entt/entity/handle.hpp>
#include <yaml-cpp/node/node.h>

#include <loki/core/runtimeObject/BaseObject.hpp>

namespace loki::system {

class Component;

#if 0
const core::TypeInfo& getComponentListTypeInfo();

namespace details {
template <class Comp>
  requires std::is_base_of_v<Component, Comp>
core::Factory getComponentFactory();

core::Factory getActorFactory();
}  // namespace details
#endif

class Actor {
 public:
  Actor() = default;
  explicit Actor(entt::handle handle) : handle(handle) {}

  void setName(std::string&& name);
  [[nodiscard]] const std::string& getName() const;
  void setTransformable(sf::Transformable&& transform);
  [[nodiscard]] const sf::Transformable& getTransformable() const;
  [[nodiscard]] const sf::Transform& getTransform() const;

  template <class Comp>
  [[nodiscard]] Comp* getComponent() {
    return handle.try_get<Comp>();
  }

  template <class Comp>
  [[nodiscard]] const Comp* getComponent() const {
    return handle.try_get<Comp>();
  }

 private:
  friend class Scene;
  void loadFromYaml(const YAML::Node& node);

 private:
  friend class ComponentRegistry;
  entt::handle handle;

#if 0
  std::vector<Component*> components;

  // For reflection
  friend const core::TypeInfo& getComponentListTypeInfo();
  friend struct ComponentSlot;
  template <class Comp>
    requires std::is_base_of_v<Component, Comp>
  friend core::Factory details::getComponentFactory();

  REFLECTION_CLASS_DECLARE(Actor)
#endif
};

}  // namespace loki::system

#if 0
REFLECTION_CLASS_BEGIN_NO_FACTORY(loki::system::Actor)
REFLECTION_CLASS_FACTORY(loki::system::details::getActorFactory())
REFLECTION_CLASS_FIELD_CUSTOM(
    loki::system::getComponentListTypeInfo(),
    "components",
    true,
    [](void* obj) -> TmpObj { return TmpObj::fromPtrNonOwned(obj); },
    [](const void* obj) -> ConstTmpObj { return ConstTmpObj::fromPtrNonOwned(obj); },
    [](void* obj, void* data) { assert(false && "Not implemented!"); })
REFLECTION_CLASS_END()
#endif