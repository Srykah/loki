#pragma once

#include <SFML/System/Time.hpp>
#include <entt/entt.hpp>

#include <loki/core/runtimeObject/BaseObject.hpp>
#include <loki/system/ecs/ComponentTraits.hpp>

template <>
struct std::hash<entt::type_info> {
  std::size_t operator()(const entt::type_info& typeInfo) const noexcept { return typeInfo.hash(); }
};

namespace loki::system {

class Actor;
class Component;
class DrawableComponent;

using InitMethod = std::function<void(void*)>;
using UpdateMethod = std::function<void(void*, sf::Time)>;

namespace details {
template <class Comp>
concept IsAComponent = std::is_base_of_v<Component, Comp>;
template <class T>
concept InitDelegate = std::is_invocable_v<T, const InitMethod&, void*>;
template <class T>
concept UpdateDelegate = std::is_invocable_v<T, const UpdateMethod&, void*, sf::Time>;
template <class T>
concept DrawDelegate = std::is_invocable_v<T, const DrawableComponent&>;
}  // namespace details

class ComponentRegistry : public core::BaseObject {
 public:
  template <details::IsAComponent Comp>
  void registerComponent();

  const BaseComponentTraits* getTraits(const entt::type_info& type) const;

 private:
  friend Actor;
  void* addComponentToActor(Actor& actor, const std::string& compName) const;

 private:
  std::unordered_map<std::string, std::function<Component&(entt::handle)>> componentFactories;
  std::unordered_map<entt::type_info, std::unique_ptr<BaseComponentTraits>> componentTraits;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(ComponentRegistry)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::core::BaseObject, loki::system::ComponentRegistry)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::ComponentRegistry)

#include "ComponentRegistry.hxx"
