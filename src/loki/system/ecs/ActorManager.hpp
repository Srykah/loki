#pragma once

#include <functional>
#include <map>

#include <SFML/System/Time.hpp>
#include <entt/entity/registry.hpp>

namespace loki::system {

class ActorManager {
 public:
  void update(sf::Time delta);

  template <class Comp>
  void registerComponent(int priority = 0);

 private:
  class GroupBase {
   public:
    virtual ~GroupBase() = default;
    virtual void update(sf::Time delta) = 0;
  };
  template <class Comp>
  class Group : public GroupBase {
   public:
    explicit Group(entt::registry& registry);
    ~Group() override = default;
    void update(sf::Time delta) override;

   private:
    entt::registry& registry;
    // decltype(entt::registry{}.group<Comp>()) group;
  };

  entt::registry registry;
  std::map<int, std::vector<std::unique_ptr<GroupBase>>> groups;
};

template <class Comp>
ActorManager::Group<Comp>::Group(entt::registry& registry)
    : registry(registry)
//: group(registry.group<Comp>())
{}

template <class Comp>
void ActorManager::Group<Comp>::update(sf::Time delta) {
  for (auto& comp : registry.view<Comp>()) {
    comp.update(delta);
  }

  /*
  for (auto& comp : group) {
    comp.update(delta);
  }
  */
}

template <class Comp>
void ActorManager::registerComponent(int priority) {
  groups[priority].emplace_back(registry);
}

}  // namespace loki::system
