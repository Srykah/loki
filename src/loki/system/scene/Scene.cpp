#include "Scene.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace loki::system {

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) {
  for (auto& layer : layers) {
    if (sortOnNextDraw) {
      std::sort(layer.begin(), layer.end(),
                [](const auto& leftPtr, const auto& rightPtr) {
                  return leftPtr->zIndex < rightPtr->zIndex;
                });
    }
    for (const auto& node : layer) {
      target.draw(node->drawable, states);
    }
  }
  sortOnNextDraw = false;
}

void Scene::addNode(SceneNode::Ptr nodePtr, int layerId) {
  layers.at(layerId).push_back(std::move(nodePtr));
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

void Scene::removeNode(SceneNode* nodePtr, int layerId) {
  if (layerId == -1) {
    for (auto& layer : layers) {
      layer.erase(std::remove_if(layer.begin(), layer.end(),
                                 [&](const auto& _nodePtr) {
                                   return *_nodePtr == nodePtr;
                                 }),
                  layer.end());
    }
  }
}

}  // namespace loki::system
