#pragma once

#include <span>

#include <SFML/Graphics/Transformable.hpp>
#include <entt/entt.hpp>
#include <yaml-cpp/node/node.h>

#include <loki/system/ecs/ComponentVisitor.hpp>

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
  [[nodiscard]] const sf::FloatRect& getLocalBox() const;
  [[nodiscard]] Actor getParent() const;
  [[nodiscard]] std::span<Actor> getChildren() const;

  [[nodiscard]] explicit operator bool() const;
  [[nodiscard]] bool operator==(const Actor& other) const = default;

  template <class Comp>
  [[nodiscard]] Comp* getComponent() {
    return handle.try_get<Comp>();
  }

  template <class Comp>
  [[nodiscard]] const Comp* getComponent() const {
    return handle.try_get<Comp>();
  }

  void visitComponents(const ComponentVisitor& visitor);
  void visitComponents(const ComponentTraitsFilter& compTraitsFilter, const ComponentVisitor& visitor);

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
