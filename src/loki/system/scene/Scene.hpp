#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <entt/entity/registry.hpp>
#include <nlohmann/json.hpp>

#include <loki/core/utils/Memory.hpp>
#include <loki/system/ecs/Actor.hpp>
#include <loki/system/ecs/ActorManager.hpp>

#include "SceneElement.hpp"

namespace loki::system {

class Scene {
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states);

  std::size_t addLayer();
  std::size_t removeLayer();
  void addElement(core::BorrowerPtr<SceneElement>&& elemPtr, int layerId = 0);
  void removeElement(SceneElement* elemPtr, int layerId = -1);
  void markForSort();

 private:
  using Layer = std::vector<core::BorrowerPtr<SceneElement>>;
  std::vector<Layer> layers;
  bool sortOnNextDraw = false;
  SceneNode root;
};

}  // namespace loki::system
