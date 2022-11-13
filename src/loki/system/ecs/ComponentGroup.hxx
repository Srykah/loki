#pragma once

namespace loki::system {

template <class Comp>
ComponentGroup<Comp>::ComponentGroup(entt::registry& registry)
    : registry(registry)
//: group(registry.group<Comp>())
{}

template <class Comp>
void ComponentGroup<Comp>::update(sf::Time delta) {
  for (auto& comp : registry.view<Comp>() /* group */) {
    comp.update(delta);
  }
}

}  // namespace loki::system
