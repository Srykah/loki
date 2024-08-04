#include "Scene.hpp"

#include <ranges>

#include <yaml-cpp/node/impl.h>

#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/ecs/ActorHierarchy.hpp>
#include <loki/system/ecs/Component.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>

namespace loki::system {

Scene::Scene() : root({registry, registry.create()}) {
  registry.ctx().insert_or_assign<Scene*>(this);
}

Actor Scene::instanciateActor(Actor parent) {
  entt::handle handle{registry, registry.create()};
  handle.emplace<std::string>("<unnamed>");
  handle.emplace<sf::Transformable>();
  handle.emplace<ActorHierarchy>(parent);
  return Actor{handle};
}

void Scene::visitComponents(ComponentVisitor&& compVisitor) {
  const auto& compReg = getService<ComponentRegistry>();
  // look among all component types in the registry
  for (auto& storage : registry.storage() | std::views::values) {
    // get the componentTraits associated with this component type
    auto* compTraits = compReg.getTraits(storage.type());
    if (!compTraits)
      continue;  // if no traits were found, or the component type is filtered out, ignore
    // iterate over the storage instances
    for (entt::entity entity : storage) {
      compVisitor(*compTraits, storage.value(entity));
    }
  }
}

void Scene::visitComponents(ComponentTraitsFilter&& compTraitsFilter, ComponentVisitor&& compVisitor) {
  const auto& compReg = getService<ComponentRegistry>();
  // look among all component types in the registry
  for (auto& storage : registry.storage() | std::views::values) {
    // get the componentTraits associated with this component type
    auto* compTraits = compReg.getTraits(storage.type());
    if (!compTraits || !compTraitsFilter(*compTraits))
      continue;  // if no traits were found, or the component type is filtered out, ignore
    // iterate over the storage instances
    for (entt::entity entity : storage) {
      compVisitor(*compTraits, storage.value(entity));
    }
  }
}

void Scene::loadFromYaml(const YAML::Node& sceneNode) {
  if (YAML::Node nameNode = sceneNode["name"]; nameNode && nameNode.Type() == YAML::NodeType::Scalar)
    name = nameNode.as<std::string>();
  if (YAML::Node rootNode = sceneNode["root"]; rootNode && rootNode.Type() == YAML::NodeType::Map) {
    root = instanciateActor();
    root.loadFromYaml(*this, rootNode);
  }
}

}  // namespace loki::system