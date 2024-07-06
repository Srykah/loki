#include "Scene.hpp"

#include <ranges>

#include <SFML/Graphics/RenderTarget.hpp>
#include <yaml-cpp/node/impl.h>

#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/ecs/ActorHierarchy.hpp>
#include <loki/system/ecs/Component.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>
#include <loki/system/render/RenderQueue.hpp>

namespace loki::system {

Scene::Scene() : root({registry, registry.create()}) {}

Actor Scene::instanciateActor(Actor parent) {
  entt::handle handle{registry, registry.create()};
  handle.emplace<std::string>("<unnamed>");
  handle.emplace<sf::Transformable>();
  handle.emplace<ActorHierarchy>(parent);
  return Actor{handle};
}

void Scene::loadFromYaml(const YAML::Node& sceneNode) {
  if (YAML::Node nameNode = sceneNode["name"]; nameNode && nameNode.Type() == YAML::NodeType::Scalar)
    name = nameNode.as<std::string>();
  if (YAML::Node rootNode = sceneNode["root"]; rootNode && rootNode.Type() == YAML::NodeType::Map) {
    root = instanciateActor();
    root.loadFromYaml(*this, rootNode);
  }
}

void Scene::update(sf::Time dt) {
  const auto& compReg = getService<ComponentRegistry>();
  // look among all component types in the registry
  for (auto& storage : registry.storage() | std::views::values) {
    // get the componentTraits associated with this component type
    auto* compTraits = compReg.getTraits(storage.type());
    if (!compTraits)
      continue;  // if no traits were found, ignore
    // iterate over the storage instances
    for (entt::entity entity : storage) {
      // get the component as a Component*
      auto& comp = compTraits->getAsComponent(storage.value(entity));
      // update it (could do all steps at once)
      if (comp.getStatus() == Component::Status::CREATED)
        comp.startInit();
      if (comp.getStatus() == Component::Status::LOADING_RESOURCES)
        continue;  // wait
      if (comp.getStatus() == Component::Status::RESOURCES_LOADED)
        comp.finalizeInit();
      if (comp.getStatus() == Component::Status::READY)
        comp.update(dt);
      // if (comp.getStatus() == Component::Status::DEINIT) // todo
    }
  }
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  RenderQueue renderQueue;
  const auto& compReg = getService<ComponentRegistry>();
  // look among all component types in the registry
  for (const auto& storage : registry.storage() | std::views::values) {
    // get the componentTraits associated with this component type
    auto* compTraits = compReg.getTraits(storage.type());
    if (!compTraits || (!compTraits->isDrawable() && !compTraits->isDebugDrawable()))
      continue;  // if no traits were found or if the type isn't (debug) drawable, ignore
    // iterate over the storage instances
    for (entt::entity entity : storage) {
      // get as a Component
      const auto& comp = compTraits->getAsComponent(storage.value(entity));
      // if it is not ready, ignore it
      if (comp.getStatus() != Component::Status::READY)
        continue;
      if (auto* drawable = compTraits->getAsDrawable(comp)) {
        // if the component is a Drawable, add it to the render queue
        renderQueue.registerDrawable(drawable->getDrawOrder(), drawable);
      }
      if (auto* debugDrawable = compTraits->getAsDebugDrawable(comp)) {
        // if the component is a DebugDrawable, add it to the render queue
        renderQueue.registerDebugDrawable(debugDrawable->getDebugDrawOrder(), debugDrawable);
      }
    }
  }

  // render the queue
  target.draw(renderQueue, states);
}

}  // namespace loki::system