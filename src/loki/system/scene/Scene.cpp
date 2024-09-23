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
  Actor actor{handle};
  handle.emplace<std::string>("<unnamed>");
  handle.emplace<sf::Transformable>();
  handle.emplace<sf::FloatRect>(-1.f, -1.f, 2.f, 2.f);
  handle.emplace<ActorHierarchy>(parent);
  if (parent)
    parent.getComponent<ActorHierarchy>()->children.push_back(actor);
  return actor;
}

void Scene::visitComponents(const ActorFilter& actorFilter,
                            const ComponentTraitsFilter& compTraitsFilter,
                            const ComponentVisitor& compVisitor) {
  const auto& compReg = getService<ComponentRegistry>();
  // look among all component types in the registry
  for (auto& storage : registry.storage() | std::views::values) {
    // get the componentTraits associated with this component type
    auto* compTraits = compReg.getTraits(storage.type());
    if (!compTraits || !compTraitsFilter(*compTraits))
      continue;  // if no traits were found, or the component type is filtered out, ignore
    // iterate over the storage instances
    for (entt::entity entity : storage) {
      if (!actorFilter(Actor{entt::handle{registry, entity}}))
        continue;
      compVisitor(*compTraits, storage.value(entity));
    }
  }
}

void Scene::visitComponents(const ActorFilter& actorFilter, const ComponentVisitor& compVisitor) {
  visitComponents(actorFilter, [](const BaseComponentTraits&) { return true; }, compVisitor);
}

void Scene::visitComponents(const ComponentTraitsFilter& compTraitsFilter, const ComponentVisitor& compVisitor) {
  visitComponents([](Actor) { return true; }, compTraitsFilter, compVisitor);
}

void Scene::visitComponents(const ComponentVisitor& compVisitor) {
  visitComponents([](Actor) { return true; }, [](const BaseComponentTraits&) { return true; }, compVisitor);
}

void Scene::visitActorComponents(Actor actor,
                                 const ComponentTraitsFilter& compTraitsFilter,
                                 const ComponentVisitor& compVisitor) {
  visitComponents([actor](Actor _actor) { return _actor == actor; }, [](const BaseComponentTraits&) { return true; },
                  compVisitor);
}

void Scene::visitActorComponents(Actor actor, const ComponentVisitor& compVisitor) {
  visitComponents([actor](Actor _actor) { return _actor == actor; }, [](const BaseComponentTraits&) { return true; },
                  compVisitor);
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