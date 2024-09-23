#include "RenderQueue.hpp"

#include <cassert>
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
  if (overdraw) {
    for (const auto& drawList : drawLists | std::views::values) {
      for (const auto* drawable : drawList.drawables) {
        assert(drawable);
        target.draw(*drawable, states);
      }
    }
    for (const auto& drawList : drawLists | std::views::values) {
      for (const auto* debugDrawable : drawList.debugDrawables) {
        assert(debugDrawable);
        debugDrawable->debugDraw(target, states);
      }
    }
  } else {
    for (const auto& drawList : drawLists | std::views::values) {
      for (const auto* drawable : drawList.drawables) {
        assert(drawable);
        target.draw(*drawable, states);
      }
      for (const auto* debugDrawable : drawList.debugDrawables) {
        assert(debugDrawable);
        debugDrawable->debugDraw(target, states);
      }
    }
  }
}

void RenderQueue::clear() {
  drawLists.clear();
}

void RenderQueue::setOverdraw(bool flag) {
  overdraw = flag;
}

}  // namespace loki::system