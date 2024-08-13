#pragma once

#include <yaml-cpp/node/node.h>

#include <loki/system/ecs/Actor.hpp>

namespace loki::system {

using ActorFilter = std::function<bool(Actor)>;

class Scene final {
 public:
  Scene();

  [[nodiscard]] const Actor& getRoot() const { return root; }

  [[nodiscard]] Actor instanciateActor(Actor parent = {});

  void visitComponents(const ActorFilter& actorFilter,
                       const ComponentTraitsFilter& compTraitsFilter,
                       const ComponentVisitor& compVisitor);
  void visitComponents(const ActorFilter& actorFilter, const ComponentVisitor& compVisitor);
  void visitComponents(const ComponentTraitsFilter& compTraitsFilter, const ComponentVisitor& compVisitor);
  void visitComponents(const ComponentVisitor& compVisitor);
  void visitActorComponents(Actor actor,
                            const ComponentTraitsFilter& compTraitsFilter,
                            const ComponentVisitor& compVisitor);
  void visitActorComponents(Actor actor, const ComponentVisitor& compVisitor);

 private:
  friend class SceneManager;
  void loadFromYaml(const YAML::Node& sceneNode);

 private:
  std::string name;
  entt::registry registry;
  Actor root;
};

}  // namespace loki::system
