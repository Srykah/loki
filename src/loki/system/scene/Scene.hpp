#pragma once

#include <filesystem>

#include <loki/system/ecs/Actor.hpp>

namespace YAML {
class Node;
}

namespace loki::system {

class ComponentRegistry;

class Scene final {
 public:
  Scene();

  [[nodiscard]] std::string_view getName() const { return name; }
  [[nodiscard]] const Actor& getRoot() const { return root; }

  void setPath(const std::filesystem::path& pathName);
  [[nodiscard]] const std::filesystem::path& getPath() const { return path; }
  void loadFromYaml(const YAML::Node& sceneNode);
  void saveToYaml();

  [[nodiscard]] Actor instanciateActor(Actor parent = {});

  void visitActors(ActorVisitor&& actorVisitor);
  void visitComponents(ActorFilter&& actorFilter,
                       ComponentTraitsFilter&& compTraitsFilter,
                       ComponentVisitor&& compVisitor);
  void visitComponents(ActorFilter&& actorFilter, ComponentVisitor&& compVisitor);
  void visitComponents(ComponentTraitsFilter&& compTraitsFilter, ComponentVisitor&& compVisitor);
  void visitComponents(ComponentVisitor&& compVisitor);
  void visitActorComponents(Actor actor, ComponentTraitsFilter&& compTraitsFilter, ComponentVisitor&& compVisitor);
  void visitActorComponents(Actor actor, ComponentVisitor&& compVisitor);

 private:
  std::string name;
  std::filesystem::path path;
  entt::registry registry;
  const ComponentRegistry& componentRegistry;
  Actor root;
};

}  // namespace loki::system
