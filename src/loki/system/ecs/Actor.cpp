#include "Actor.hpp"

#include <box/BoundingBoxComponent.hpp>
#include <serialization/yaml/toYaml.hpp>

#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/core/rtti/RuntimeObjectRegistry.hpp>
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

const sf::FloatRect& Actor::getLocalBox() const {
  return getComponent<BoundingBoxComponent>()->getLocalBox();
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

void Actor::visitComponents(const ComponentVisitor& visitor) {
  getScene().visitActorComponents(*this, visitor);
}

void Actor::visitComponents(const ComponentTraitsFilter& compTraitsFilter, const ComponentVisitor& visitor) {
  getScene().visitActorComponents(*this, compTraitsFilter, visitor);
}

Scene& Actor::getScene() const {
  return *handle.registry()->ctx().get<Scene*>();
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

void Actor::saveToYaml(YAML::Emitter& emitter) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name" << YAML::Value << *getComponent<std::string>();
  if (const auto& transform = getTransformable(); transform.getTransform() != sf::Transform{})
    emitter << YAML::Key << "transform" << YAML::Value << transform;
  emitter << YAML::Key << "components" << YAML::Value << YAML::BeginSeq;
  visitComponents([&](const BaseComponentTraits& compTraits, const void* comp) {
    if (&compTraits.getTypeInfo() == &core::getTypeInfo<BoundingBoxComponent>())
      return;  // skip bounding box component, it is runtime only
    core::toYaml(emitter, comp, compTraits.getTypeInfo());
  });
  emitter << YAML::EndSeq;
  if (auto children = getChildren(); !children.empty()) {
    emitter << YAML::Key << "children" << YAML::Value << YAML::BeginSeq;
    for (const Actor child : children)
      emitter << child;
    emitter << YAML::EndSeq;
  }
  emitter << YAML::EndMap;
}

YAML::Emitter& operator<<(YAML::Emitter& emitter, Actor actor) {
  actor.saveToYaml(emitter);
  return emitter;
}

}  // namespace loki::system
