#include "Scene.hpp"

#include <map>
#include <ranges>

#include <SFML/Graphics/RenderTarget.hpp>

#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>
#include <loki/system/ecs/DrawableComponent.hpp>

namespace loki::system {

Scene::Scene() : root({registry, registry.create()}) {}

Actor Scene::instanciateActor(entt::entity parent) {
#if 0
  const auto& storageForComp = scene->registry.storage(entt::id_type {0})->second;
  for (const auto& entity : storageForComp.) {
    storageForComp.get(entity);
  }
#endif
  entt::handle handle{registry, registry.create()};
  handle.emplace<std::string>("<unnamed>");
  handle.emplace<sf::Transformable>();
  return Actor{handle};
}

void Scene::loadFromYaml(const YAML::Node& sceneNode) {
  if (const YAML::Node& nameNode = sceneNode["name"]; nameNode && nameNode.Type() == YAML::NodeType::Scalar)
    name = nameNode.as<std::string>();
  if (const YAML::Node& rootNode = sceneNode["root"]; rootNode && rootNode.Type() == YAML::NodeType::Map) {
    root = instanciateActor();
    root.loadFromYaml(rootNode);
  }
}

void Scene::update(sf::Time dt) {
  auto& compReg = getService<ComponentRegistry>();
  compReg.visitInitableComponents([](const InitMethod& initMethod, void* obj) -> void {
    initMethod(obj);  // execute immediately
  });
  compReg.visitUpdatableComponents(
      [](const UpdateMethod& updateMethod, void* obj, sf::Time dt) -> void {
        updateMethod(obj, dt);  // execute immediately
      },
      dt);
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // prepare draw list
  // todo change to flat_map when available
  std::multimap<DrawOrder, const sf::Drawable*> drawables;
  getService<ComponentRegistry>().visitDrawableComponents(
      [&drawables](const DrawableComponent& comp) { drawables.emplace(comp.getDrawOrder(), &comp); });
  for (const Drawable* drawable : drawables | std::views::values) {
    target.draw(*drawable, states);
  }
}

}  // namespace loki::system