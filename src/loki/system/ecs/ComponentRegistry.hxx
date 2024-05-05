#include <loki/core/reflection/TypeInfo.hpp>

namespace loki::system {

namespace details {
template <class Comp>
concept IsADrawableComponent = std::is_base_of_v<DrawableComponent, Comp>;
template <class Comp>
concept HasInit = requires { std::declval<Comp>().init(); };
template <class Comp>
concept HasUpdate = requires { std::declval<Comp>().update(sf::Time{}); };
}  // namespace details

template <details::IsAComponent Comp>
void ComponentRegistry::registerComponent() {
  const core::ClassInfo& classInfo = std::get<core::ClassInfo>(core::getTypeInfo<Comp>().info);
  std::string compName{classInfo.id};
  auto compId = entt::type_id<Comp>();
  componentFactories.try_emplace(std::move(compName), [](entt::handle handle) -> Component& {
    return static_cast<Component&>(handle.emplace<Comp>());
  });
  if constexpr (details::HasInit<Comp>) {
    InitData& initData = initSteps.try_emplace(compId).first->second;
    initData.method = [](void* comp) -> void { static_cast<Comp*>(comp)->init(); };
    initData.observerConnector = [](entt::observer& observer, entt::registry& registry) {
      observer.connect(registry, entt::collector.group<Comp>());
    };
    if (registry) {
      initData.observerConnector(initData.observer, *registry);
    }
  }
  if constexpr (details::HasUpdate<Comp>) {
    updateSteps.try_emplace(compId, [](void* comp, sf::Time dt) -> void { static_cast<Comp*>(comp)->update(dt); });
  }
  if constexpr (details::IsADrawableComponent<Comp>) {
    drawableCasts.try_emplace(compId, [](const void* comp) -> const DrawableComponent& {
      return static_cast<const DrawableComponent&>(*static_cast<const Comp*>(comp));
    });
  }
}

void ComponentRegistry::visitInitableComponents(details::InitDelegate auto&& initDelegate) {
  assert(registry);
  // look among all component types in the registry
  for (auto&& [_, storage] : registry->storage()) {
    // if the current component type is initable
    if (auto it = initSteps.find(storage.type()); it != initSteps.end()) {
      // iterate over the entities whose component has been recently added to the registry
      it->second.observer.each([&](entt::entity entity) {
        // and call the initDelegate over them
        initDelegate(it->second.method, storage.get(entity));
      });
    }
  }
}

void ComponentRegistry::visitUpdatableComponents(details::UpdateDelegate auto&& updateDelegate, sf::Time dt) {
  assert(registry);
  // look among all component types in the registry
  for (auto&& [_, storage] : registry->storage()) {
    // if the current component type is updatable
    if (auto it = updateSteps.find(storage.type()); it != updateSteps.end()) {
      // iterate over its instances
      for (entt::entity entity : storage) {
        // and call the updateDelegate over them
        updateDelegate(it->second, storage.get(entity), dt);
      }
    }
  }
}

void ComponentRegistry::visitDrawableComponents(details::DrawDelegate auto&& drawDelegate) const {
  assert(registry);
  // look among all component types in the registry
  for (auto&& [_, storage] : registry->storage()) {
    // if the current component type is drawable
    if (auto it = drawableCasts.find(storage.type()); it != drawableCasts.end()) {
      // iterate over its instances
      for (const entt::entity entity : storage) {
        // and call the drawDelegate over the casted component
        drawDelegate(it->second(storage.get(entity)));
      }
    }
  }
}

}  // namespace loki::system