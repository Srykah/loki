#include "Actor.hpp"

#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/core/rtti/RuntimeObjectRegistry.hpp>
#include <loki/core/serialization/yaml/fromYaml.hpp>
#include <loki/core/serialization/yaml/toYaml.hpp>
#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/box/BoundingBoxComponent.hpp>
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

void Actor::visitComponents(ComponentVisitor&& visitor) {
  getScene().visitActorComponents(*this, std::move(visitor));
}

void Actor::visitComponents(ConstComponentVisitor&& visitor) const {
  getScene().visitActorComponents(*this, std::move(visitor));
}

void Actor::visitComponents(ComponentTraitsFilter&& compTraitsFilter, ComponentVisitor&& visitor) {
  getScene().visitActorComponents(*this, std::move(compTraitsFilter), std::move(visitor));
}

void Actor::visitComponents(ComponentTraitsFilter&& compTraitsFilter, ConstComponentVisitor&& visitor) const {
  getScene().visitActorComponents(*this, std::move(compTraitsFilter), std::move(visitor));
}

LifeCycleStep Actor::getStatus() const {
  auto step = std::to_underlying(LifeCycleStep::Created);
  visitComponents([&step](const BaseComponentTraits& compTraits, const void* obj) {
    step = std::max(step, std::to_underlying(compTraits.getAsComponent(obj).getLifeCycleStep()));
  });
  return static_cast<LifeCycleStep>(step);
}

Scene& Actor::getScene() const {
  return *handle.registry()->ctx().get<Scene*>();
}

void Actor::loadFromYaml(Scene& scene, const ryml::ConstNodeRef& node) {
  if (ryml::ConstNodeRef nameNode = node["name"]; !nameNode.invalid()) {
    std::string name;
    node >> name;
    setName(std::move(name));
  }
  if (ryml::ConstNodeRef transformNode = node["transform"]; !transformNode.invalid()) {
    core::fromYaml(transformNode, *getComponent<sf::Transformable>());
  }
  const auto& compReg = getService<ComponentRegistry>();
  const auto& classReg = getService<core::RuntimeObjectRegistry>();
  for (ryml::ConstNodeRef componentNode : node["components"]) {
    ryml::ConstNodeRef compTypeNode = componentNode["__type__"];
    if (compTypeNode.invalid() || !compTypeNode.type().is_val()) {
      return;
    }
    std::string compType;
    compTypeNode >> compType;
    void* newComp = compReg.addComponentToActor(*this, compType);
    auto* compTypeInfo = classReg.getRuntimeTypeInfo(compType);
    core::fromYaml(componentNode, newComp, *compTypeInfo);
  }
  for (auto childNode : node["children"]) {
    scene.instanciateActor(*this).loadFromYaml(scene, childNode);
  }
}

void Actor::saveToYaml(ryml::NodeRef destNode) const {
  destNode |= ryml::MAP;
  destNode.append_child() << ryml::key("name") << *getComponent<std::string>();
  if (const auto& transform = getTransformable(); transform.getTransform() != sf::Transform{}) {
    auto transformNode = destNode.append_child();
    transformNode << ryml::key("transform");
    core::toYaml(transformNode, transform);
  }
  auto componentsNode = destNode.append_child();
  componentsNode << ryml::key("components");
  componentsNode |= ryml::SEQ;
  visitComponents([&](const BaseComponentTraits& compTraits, const void* comp) {
    if (&compTraits.getTypeInfo() == &core::getTypeInfo<BoundingBoxComponent>()) {
      return;  // skip bounding box component, it is runtime only
    }
    core::toYaml(componentsNode.append_child(), comp, compTraits.getTypeInfo());
  });
  if (auto children = getChildren(); !children.empty()) {
    auto childrenNode = destNode.append_child();
    childrenNode << ryml::key("children");
    childrenNode |= ryml::SEQ;
    for (const Actor child : children) {
      child.saveToYaml(childrenNode.append_child());
    }
  }
}

}  // namespace loki::system
