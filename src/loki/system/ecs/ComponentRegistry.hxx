#include <loki/core/reflection/TypeInfo.hpp>

namespace loki::system {

template <details::IsAComponent Comp>
void ComponentRegistry::registerComponent() {
  const core::ClassInfo& classInfo = std::get<core::ClassInfo>(core::getTypeInfo<Comp>().info);
  std::string compName{classInfo.id};
  componentFactories.try_emplace(std::move(compName), [](entt::handle handle) -> Component& {
    return static_cast<Component&>(handle.emplace<Comp>());
  });
  componentTraits.try_emplace(entt::type_id<Comp>(), std::make_unique<ComponentTraits<Comp>>());
}

}  // namespace loki::system