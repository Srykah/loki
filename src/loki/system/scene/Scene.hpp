#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <entt/entity/registry.hpp>
#include <loki/core/utils/Memory.hpp>
#include <loki/system/ecs/Actor.hpp>
#include <loki/system/ecs/ActorManager.hpp>

namespace loki::system {

struct SceneNode {
  int zIndex = 0;
  sf::Drawable& drawable;

  using Ptr = core::BorrowerPtr<SceneNode>;
};

class Scene {
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states);

  std::size_t addLayer();
  std::size_t removeLayer();
  void addNode(SceneNode::Ptr nodePtr, int layerId = 0);
  void removeNode(SceneNode* nodePtr, int layerId = -1);
  void markForSort();

 private:
  using Layer = std::vector<SceneNode::Ptr>;
  std::vector<Layer> layers;
  bool sortOnNextDraw = false;
};

}  // namespace loki::system
