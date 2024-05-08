#include "Actor.hpp"

#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/core/runtimeObject/RuntimeObjectRegistry.hpp>
#include <loki/core/serialization/yaml/fromYaml.hpp>
#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/ecs/ActorHierarchy.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>
#include <loki/system/scene/SceneManager.hpp>

namespace loki::system {

void Actor::setName(std::string&& name) {
  *getComponent<std::string>() = std::move(name);
}

const std::string& Actor::getName() const {
  return *getComponent<std::string>();
}

void Actor::setTransformable(sf::Transformable&& transform) {
  *getComponent<sf::Transformable>() = std::move(transform);
}

const sf::Transformable& Actor::getTransformable() const {
  return *getComponent<sf::Transformable>();
}

const sf::Transform& Actor::getLocalTransform() const {
  return getTransformable().getTransform();
}

sf::Transform Actor::getGlobalTransform() const {
  if (Actor parent = getParent()) {
    return parent.getGlobalTransform() * getLocalTransform();
  }
  return getLocalTransform();
}

Actor Actor::getParent() const {
  return getComponent<ActorHierarchy>()->parent;
}

std::span<Actor> Actor::getChildren() const {
  return const_cast<Actor*>(this)->getComponent<ActorHierarchy>()->children;
}

Actor::operator bool() const {
  return static_cast<bool>(handle);
}

void Actor::loadFromYaml(Scene& scene, const YAML::Node& node) {
  if (const YAML::Node& nameNode = node["name"]) {
    setName(nameNode.as<std::string>());
  }
  if (const YAML::Node& transformNode = node["transform"]) {
    core::fromYaml(transformNode, *getComponent<sf::Transformable>());
  }
  const auto& compReg = getService<ComponentRegistry>();
  const auto& classReg = getService<core::RuntimeObjectRegistry>();
  for (const YAML::Node& componentNode : node["components"]) {
    const YAML::Node& compTypeNode = componentNode["__type__"];
    if (!compTypeNode || compTypeNode.Type() != YAML::NodeType::Scalar)
      return;
    std::string compType = compTypeNode.as<std::string>();
    void* newComp = compReg.addComponentToActor(*this, compType);
    auto* compTypeInfo = classReg.getRuntimeTypeInfo(compType);
    core::fromYaml(componentNode, newComp, *compTypeInfo);
  }
  for (const YAML::Node& childNode : node["children"]) {
    scene.instanciateActor(*this).loadFromYaml(scene, childNode);
  }
}

}  // namespace loki::system
