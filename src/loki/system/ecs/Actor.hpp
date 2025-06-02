#pragma once

#include <span>

#include <SFML/Graphics/Transformable.hpp>
#include <ecs/LifeCycleStep.hpp>
#include <entt/entt.hpp>
#include <yaml-cpp/emitter.h>
#include <yaml-cpp/node/node.h>

#include <loki/system/ecs/VisitorConcepts.hpp>

namespace loki::system {

class Component;
class Scene;

class Actor {
 public:
  Actor() = default;

  void loadFromYaml(Scene& scene, const YAML::Node& node);
  void saveToYaml(YAML::Emitter& emitter);
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

  void visitComponents(ComponentVisitor&& visitor);
  void visitComponents(ConstComponentVisitor&& visitor) const;
  void visitComponents(ComponentTraitsFilter&& compTraitsFilter, ComponentVisitor&& visitor);
  void visitComponents(ComponentTraitsFilter&& compTraitsFilter, ConstComponentVisitor&& visitor) const;

  [[nodiscard]] LifeCycleStep getStatus() const;

  [[nodiscard]] Scene& getScene() const;

 private:
  friend Scene;
  explicit Actor(entt::handle handle) : handle(handle) {}

 private:
  friend class ComponentRegistry;
  entt::handle handle;
};

YAML::Emitter& operator<<(YAML::Emitter& emitter, Actor actor);

}  // namespace loki::system
