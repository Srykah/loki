#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <entt/entity/registry.hpp>
#include <yaml-cpp/node/node.h>

#include <loki/system/ecs/Actor.hpp>

namespace loki::system {

class Scene final : public sf::Drawable {
 public:
  Scene();

  [[nodiscard]] const Actor& getRoot() const { return root; }

  [[nodiscard]] Actor instanciateActor(Actor parent = {});

 private:
  friend class SceneManager;
  void loadFromYaml(const YAML::Node& sceneNode);
  void update(sf::Time dt);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  std::string name;
  entt::registry registry;
  Actor root;
};

}  // namespace loki::system
