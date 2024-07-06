#include "RenderQueue.hpp"

#include <ranges>

#include <SFML/Graphics/RenderTarget.hpp>

namespace loki::system {

void RenderQueue::registerDrawable(DrawOrder drawOrder, const system::Drawable* drawable) {
  drawLists[drawOrder].drawables.push_back(drawable);
}

void RenderQueue::registerDebugDrawable(DrawOrder drawOrder, const DebugDrawable* debugDrawable) {
  drawLists[drawOrder].debugDrawables.push_back(debugDrawable);
}

void RenderQueue::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const auto& drawList : drawLists | std::views::values) {
    for (const auto* drawable : drawList.drawables)
      drawable->draw(target, states);
    for (const auto* debugDrawable : drawList.debugDrawables)
      debugDrawable->debugDraw(target, states);
  }
}

}  // namespace loki::system