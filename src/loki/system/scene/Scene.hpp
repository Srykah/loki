#pragma once

#include <filesystem>

#include <yaml-cpp/node/node.h>

#include <loki/system/ecs/Actor.hpp>

namespace loki::system {

using ActorFilter = std::function<bool(Actor)>;

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
  std::string name;
  std::filesystem::path path;
  entt::registry registry;
  const ComponentRegistry& componentRegistry;
  Actor root;
};

}  // namespace loki::system
