#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <entt/entity/registry.hpp>
#include <yaml-cpp/node/node.h>

#include <loki/system/ecs/Actor.hpp>

#if 0
#include <loki/core/reflection/classMacros.hpp>
#endif

namespace loki::system {

class Scene : public sf::Drawable {
 public:
  Scene();

  [[nodiscard]] const Actor& getRoot() const { return root; }

  [[nodiscard]] Actor instanciateActor(entt::entity parent = entt::null);

 private:
  friend class SceneManager;
  void loadFromYaml(const YAML::Node& sceneNode);
  void update(sf::Time dt);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  std::string name;
  entt::registry registry;
  Actor root;

#if 0
  REFLECTION_CLASS_DECLARE(Scene)
#endif
};

}  // namespace loki::system

#if 0
REFLECTION_CLASS_BEGIN(loki::system::Scene)
REFLECTION_CLASS_FIELD(loki::system::Scene, root)
REFLECTION_CLASS_END()
#endif
