#pragma once

#include <yaml-cpp/node/node.h>

#include <loki/system/ecs/Actor.hpp>

namespace loki::system {
class BaseComponentTraits;

using ComponentVisitor = std::function<void(const BaseComponentTraits&, void*)>;
using ComponentTraitsFilter = std::function<bool(const BaseComponentTraits&)>;

class Scene final {
 public:
  Scene();

  [[nodiscard]] const Actor& getRoot() const { return root; }

  [[nodiscard]] Actor instanciateActor(Actor parent = {});

  void visitComponents(ComponentVisitor&& compVisitor);
  void visitComponents(ComponentTraitsFilter&& compTraitsFilter, ComponentVisitor&& compVisitor);

 private:
  friend class SceneManager;
  void loadFromYaml(const YAML::Node& sceneNode);

 private:
  std::string name;
  entt::registry registry;
  Actor root;
};

}  // namespace loki::system
