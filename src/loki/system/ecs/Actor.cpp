#include "Actor.hpp"

#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/core/serialization/yaml/fromYaml.hpp>
#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/scene/SceneManager.hpp>

#include "ComponentRegistry.hpp"
#include "loki/core/runtimeObject/RuntimeObjectRegistry.hpp"

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

const sf::Transform& Actor::getTransform() const {
  return getTransformable().getTransform();
}

void Actor::loadFromYaml(const YAML::Node& node) {
  if (const YAML::Node& nameNode = node["name"]; nameNode && nameNode.Type() == YAML::NodeType::Scalar) {
    setName(nameNode.as<std::string>());
  }
  if (const YAML::Node& transformNode = node["transform"];
      transformNode && transformNode.Type() == YAML::NodeType::Scalar) {
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
}

}  // namespace loki::system

#if 0

#include "ComponentSlot.hpp"

namespace loki::system {

const core::TypeInfo& getComponentListTypeInfo() {
  static const core::TypeInfo COMPONENTLIST_TYPEINFO{
      .info = core::ListInfo{.valueType = core::getTypeInfo<ComponentSlot>(),
                       .isSortable = false,
                       .elemGetter = [](void* obj, std::size_t index) -> core::TmpObj {
                         return core::TmpObj::makeOwned<ComponentSlot>(core::to<Actor>(obj), index);
                       },
                       .elemGetterConst = [](const void* obj, std::size_t index) -> core::ConstTmpObj {
                         return core::ConstTmpObj::makeOwned<ComponentSlot>(const_cast<Actor&>(core::to<Actor>(obj)), index);
                       },
                       .sizeGetter = [](const void* obj) -> std::size_t { return core::to<Actor>(obj).components.size(); },
                       .elemSetter =
                           [](void* obj, std::size_t index, void* data) {
  // nothing to do!
#if 0
                             auto& actor = core::to<Actor>(obj);
                             auto& compSlot = core::to<ComponentSlot>(data);
                             assert(&compSlot.actor == &actor);
                             auto* comp = compSlot.get();
                             assert(comp);
                             const core::TypeInfo& compTypeInfo = comp->getTypeInfo();
                             core::TmpObj newComp = compTypeInfo.factory(obj, core::TmpObj::Ownership::NonOwned);
                             actor.components.emplace(actor.components.begin() + index,
                                                      static_cast<Component*>(asAncestor(newComp.obj, &compTypeInfo, "Component")));
#endif
                           },
                       .elemSwapper = [](const void* obj, std::size_t indexA,
                                         std::size_t indexB) { assert(false && "Not implemented!"); },
                       .elemAdder = [](void* obj, std::size_t index) -> core::TmpObj {
                         return core::TmpObj::makeOwned<ComponentSlot>(core::to<Actor>(obj));
                       },
                       .elemEmplacer =
                           [](void* obj, std::size_t index, void* data) {
                             auto& actor = core::to<Actor>(obj);
                             auto& compSlot = core::to<ComponentSlot>(data);
                             assert(&compSlot.actor == &actor);
                             auto* comp = compSlot.get();
                             assert(comp);
                             const core::TypeInfo& compTypeInfo = comp->getClassTypeInfo();
                             core::TmpObj newComp = compTypeInfo.factory(obj, core::TmpObj::Ownership::NonOwned);
                             actor.components.emplace(
                                 actor.components.begin() + index,
                                 static_cast<Component*>(asAncestor(newComp.obj, &compTypeInfo, "Component")));
                           },
                       .elemDeleter =
                           [](void* obj, std::size_t index) {
                             auto& actor = core::to<Actor>(obj);
                             actor.components[index]->destroy();
                             actor.components.erase(actor.components.begin() + index);
                           },
                       .clear =
                           [](void* obj) {
                             auto& actor = core::to<Actor>(obj);
                             for (auto&& [_, substorage] : actor.handle.registry()->storage())
                               substorage.remove(actor.handle.entity());  // a bit awkward, but it should work
                             actor.components.clear();
                           }}};
  return COMPONENTLIST_TYPEINFO;
}

core::Factory details::getActorFactory() {
  return [](void*, core::TmpObj::Ownership ownership) -> core::TmpObj {
    return ServiceRegistry::get<SceneManager>().instanciateActor(ownership);
  };
}

}

#endif