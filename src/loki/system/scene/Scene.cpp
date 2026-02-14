#include "Scene.hpp"

#include <fstream>
#include <ranges>

#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/box/BoundingBoxComponent.hpp>
#include <loki/system/ecs/ActorHierarchy.hpp>
#include <loki/system/ecs/Component.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>

namespace loki::system {

Scene::Scene() : componentRegistry(getService<ComponentRegistry>()), root({registry, registry.create()}) {
  registry.ctx().insert_or_assign<Scene*>(this);
}

Actor Scene::instanciateActor(Actor parent) {
  entt::handle handle{registry, registry.create()};
  Actor actor{handle};
  handle.emplace<std::string>("<unnamed>");
  handle.emplace<sf::Transformable>();
  auto& bbComp = handle.emplace<BoundingBoxComponent>();
  bbComp.setActor(actor);
  handle.emplace<ActorHierarchy>(parent);
  if (parent)
    parent.getComponent<ActorHierarchy>()->children.push_back(actor);
  return actor;
}

void Scene::visitActors(ActorVisitor&& actorVisitor) {
  for (entt::entity entity : registry.view<entt::entity>()) {
    actorVisitor(Actor{entt::handle{registry, entity}});
  }
}

void Scene::visitComponents(ActorFilter&& actorFilter,
                            ComponentTraitsFilter&& compTraitsFilter,
                            ComponentVisitor&& compVisitor) {
  // look among all component types in the registry
  for (auto& storage : registry.storage() | std::views::values) {
    // get the componentTraits associated with this component type
    auto* compTraits = componentRegistry.getTraits(storage.type());
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

void Scene::visitComponents(ActorFilter&& actorFilter, ComponentVisitor&& compVisitor) {
  visitComponents(std::move(actorFilter), [](const BaseComponentTraits&) { return true; }, std::move(compVisitor));
}

void Scene::visitComponents(ComponentTraitsFilter&& compTraitsFilter, ComponentVisitor&& compVisitor) {
  visitComponents([](Actor) { return true; }, std::move(compTraitsFilter), std::move(compVisitor));
}

void Scene::visitComponents(ComponentVisitor&& compVisitor) {
  visitComponents([](Actor) { return true; }, [](const BaseComponentTraits&) { return true; }, std::move(compVisitor));
}

void Scene::visitActorComponents(Actor actor,
                                 ComponentTraitsFilter&& compTraitsFilter,
                                 ComponentVisitor&& compVisitor) {
  visitComponents([actor](Actor _actor) { return _actor == actor; }, std::move(compTraitsFilter),
                  std::move(compVisitor));
}

void Scene::visitActorComponents(Actor actor, ComponentVisitor&& compVisitor) {
  visitComponents([actor](Actor _actor) { return _actor == actor; }, [](const BaseComponentTraits&) { return true; },
                  std::move(compVisitor));
}

void Scene::setPath(const std::filesystem::path& _path) {
  path = _path;
}

void Scene::loadFromYaml(const ryml::ConstNodeRef& sceneNode) {
  if (ryml::ConstNodeRef nameNode = sceneNode["name"]; !nameNode.invalid() && nameNode.type().is_val()) {
    nameNode >> name;
  }
  if (ryml::ConstNodeRef rootNode = sceneNode["root"]; !rootNode.invalid() && rootNode.type().is_map()) {
    root = instanciateActor();
    root.loadFromYaml(*this, rootNode);
  }
}

void Scene::saveToYaml() {
  ryml::Tree tree;
  ryml::NodeRef treeNode = tree.rootref();
  treeNode |= ryml::MAP;
  treeNode.append_child() << ryml::key("name") << name;
  auto rootNode = treeNode.append_child();
  rootNode << ryml::key("root");
  root.saveToYaml(rootNode);

  std::ofstream file{path};
  file << treeNode;
}

}  // namespace loki::system