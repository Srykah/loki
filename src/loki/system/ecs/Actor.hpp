#pragma once

#include <span>

#include <SFML/Graphics/Transformable.hpp>
#include <entt/entt.hpp>
#include <yaml-cpp/node/node.h>

namespace loki::system {

class Component;
class Scene;

class Actor {
 public:
  Actor() = default;

  void setName(std::string&& name);
  [[nodiscard]] const std::string& getName() const;
  void setTransformable(sf::Transformable&& transform);
  [[nodiscard]] const sf::Transformable& getTransformable() const;
  [[nodiscard]] const sf::Transform& getLocalTransform() const;
  [[nodiscard]] sf::Transform getGlobalTransform() const;
  [[nodiscard]] Actor getParent() const;
  [[nodiscard]] std::span<Actor> getChildren() const;

  [[nodiscard]] explicit operator bool() const;

  template <class Comp>
  [[nodiscard]] Comp* getComponent() {
    return handle.try_get<Comp>();
  }

  template <class Comp>
  [[nodiscard]] const Comp* getComponent() const {
    return handle.try_get<Comp>();
  }

  [[nodiscard]] Scene& getScene() const;

 private:
  friend Scene;
  explicit Actor(entt::handle handle) : handle(handle) {}
  void loadFromYaml(Scene& scene, const YAML::Node& node);

 private:
  friend class ComponentRegistry;
  entt::handle handle;
};

}  // namespace loki::system
