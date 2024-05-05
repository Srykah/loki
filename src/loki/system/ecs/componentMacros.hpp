#pragma once

#if 0
#include <type_traits>

#include "ComponentRegistry.hpp"

namespace loki::system {
class Component;
}

namespace loki::system::details {

template <class Comp>
  requires std::is_base_of_v<Component, Comp>
class ComponentRegistrar {
 public:
  ComponentRegistrar() { ComponentRegistry::registerComponent<Comp>(); }
};

}  // namespace loki::system::details
#endif

#define REFLECTION_COMPONENT_BEGIN(Comp) \
  REFLECTION_CLASS_BEGIN(Comp)           \
  REFLECTION_CLASS_PARENT(Comp, loki::system::Component)

#if 0

#include "Actor.hpp"
#include "ComponentSlot.hpp"

namespace loki::system::details {

template <class Comp>
  requires std::is_base_of_v<Component, Comp>
core::Factory getComponentFactory() {
  return [](void* ctx, core::TmpObj::Ownership ownership) -> core::TmpObj {
    auto& compSlot = core::to<ComponentSlot>(ctx);
    Component*& comp = compSlot.get();
    assert(!comp);
    comp = &compSlot.actor.handle.emplace<Comp>();
    comp->actor = &compSlot.actor;
    return core::TmpObj::fromPtrNonOwned(comp);
  };
}

}  // namespace details

#define REFLECTION_CLASS_BEGIN_COMPONENT(Class)                   \
  REFLECTION_CLASS_BEGIN_NO_FACTORY(Class)                        \
  REFLECTION_CLASS_FACTORY(details::getComponentFactory<Class>()) \
  REFLECTION_CLASS_PARENT(Class, Component)

#endif