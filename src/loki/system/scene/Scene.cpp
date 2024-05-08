#include "Scene.hpp"

#include <map>
#include <ranges>

#include <SFML/Graphics/RenderTarget.hpp>

#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/ecs/ActorHierarchy.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>
#include <loki/system/ecs/DrawableComponent.hpp>

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
  if (const YAML::Node& nameNode = sceneNode["name"]; nameNode && nameNode.Type() == YAML::NodeType::Scalar)
    name = nameNode.as<std::string>();
  if (const YAML::Node& rootNode = sceneNode["root"]; rootNode && rootNode.Type() == YAML::NodeType::Map) {
    root = instanciateActor();
    root.loadFromYaml(*this, rootNode);
  }
}

void Scene::update(sf::Time dt) {
  const auto& compReg = getService<ComponentRegistry>();
  // look among all component types in the registry
  for (auto&& [_, storage] : registry.storage()) {
    // get the componentTraits associated with this component type
    auto* compTraits = compReg.getTraits(storage.type());
    if (!compTraits)
      continue;  // if no traits were found, ignore
    // iterate over the storage instances
    for (entt::entity entity : storage) {
      // get the component as a Component*
      auto& comp = compTraits->getAsComponent(storage.get(entity));
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
  // prepare draw list
  // todo change to flat_map when available
  std::multimap<DrawOrder, const sf::Drawable*> drawables;

  const auto& compReg = getService<ComponentRegistry>();
  // look among all component types in the registry
  for (const auto& storage : registry.storage() | std::views::values) {
    // get the componentTraits associated with this component type
    auto* compTraits = compReg.getTraits(storage.type());
    if (!compTraits || !compTraits->isDrawable())
      continue;  // if no traits were found or if the type isn't drawable, ignore
    // iterate over the storage instances
    for (entt::entity entity : storage) {
      // get the component as a DrawableComponent*
      auto* comp = compTraits->getAsDrawableComponent(storage.get(entity));
      // if it is not ready, ignore it
      if (comp->getStatus() != Component::Status::READY)
        continue;
      // add it to the draw list
      drawables.emplace(comp->getDrawOrder(), static_cast<const sf::Drawable*>(comp));
    }
  }

  // draw the list
  for (const Drawable* drawable : drawables | std::views::values) {
    target.draw(*drawable, states);
  }
}

}  // namespace loki::system