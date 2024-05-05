#pragma once

#include <SFML/System/Time.hpp>
#include <entt/entity/handle.hpp>
#include <entt/entity/observer.hpp>

#include <loki/core/runtimeObject/BaseObject.hpp>

template <>
struct std::hash<entt::type_info> {
  std::size_t operator()(const entt::type_info& typeInfo) const noexcept { return typeInfo.hash(); }
};

namespace loki::system {

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
  void setRegistry(entt::registry& registry);

  template <details::IsAComponent Comp>
  void registerComponent();

  void visitInitableComponents(details::InitDelegate auto&& initDelegate);

  void visitUpdatableComponents(details::UpdateDelegate auto&& updateDelegate, sf::Time dt);

  void visitDrawableComponents(details::DrawDelegate auto&&) const;

 private:
  void reconnectObservers();

  friend class Actor;
  void* addComponentToActor(Actor& actor, const std::string& compName) const;

 private:
  using CastToDrawableComp = std::function<const DrawableComponent&(const void*)>;
  struct InitData {
    InitMethod method;
    std::function<void(entt::observer&, entt::registry&)> observerConnector;
    entt::observer observer;
  };
  entt::registry* registry = nullptr;
  std::unordered_map<std::string, std::function<Component&(entt::handle)>> componentFactories;
  std::unordered_map<entt::type_info, InitData> initSteps;
  std::unordered_map<entt::type_info, UpdateMethod> updateSteps;
  std::unordered_map<entt::type_info, CastToDrawableComp> drawableCasts;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(ComponentRegistry)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::core::BaseObject, loki::system::ComponentRegistry)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::ComponentRegistry)

#include "ComponentRegistry.hxx"