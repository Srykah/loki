#include "Scene.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace loki::system {

#if 0
void Scene::load(const nlohmann::json& json) {
  layers.reserve(json.at("layers").size());
  for (const auto& layerData : json.at("layers")) {
    layers.emplace_back();
    auto& layer = layers.back();
    for (const auto& actorData : layerData) {
      layer.emplace_back(std::make_unique<Actor>());
    }
  }
}
#endif

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) {
  for (auto& layer : layers) {
    if (sortOnNextDraw) {
      std::ranges::sort(layer, [](const auto& leftPtr, const auto& rightPtr) {
        return leftPtr->getZIndex() < rightPtr->getZIndex();
      });
    }
    for (const auto& elem : layer) {
      target.draw(*elem, states);
    }
  }
  sortOnNextDraw = false;
}

void Scene::addElement(core::BorrowerPtr<SceneElement>&& elemPtr, int layerId) {
  layers.at(layerId).push_back(std::move(elemPtr));
  sortOnNextDraw = true;
}

void Scene::markForSort() {
  sortOnNextDraw = true;
}

std::size_t Scene::addLayer() {
  layers.emplace_back();
  return layers.size();
}

std::size_t Scene::removeLayer() {
  layers.pop_back();
  return layers.size();
}

void Scene::removeElement(SceneElement* elemPtr, int layerId) {
  if (layerId == -1) {
    for (auto& layer : layers) {
      auto removed =
          std::ranges::remove_if(layer, [elemPtr](const auto& _elemPtr) { return _elemPtr.get() == elemPtr; });
      layer.erase(removed.begin(), removed.end());
    }
  }
}

}  // namespace loki::system
