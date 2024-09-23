#include "RenderQueue.hpp"

#include <cassert>
#include <ranges>

#include <SFML/Graphics/RenderTarget.hpp>

namespace loki::system {

void RenderQueue::registerDrawable(const sf::Drawable* drawable, DrawOrder drawOrder, bool isDebug) {
  const DrawEntry newDrawEntry{.drawable = drawable, .drawOrder = drawOrder, .isDebug = isDebug};
  drawEntries.insert(
      std::ranges::upper_bound(drawEntries, newDrawEntry, overdraw ? DrawEntry::lessOverdraw : DrawEntry::less),
      newDrawEntry);
}

void RenderQueue::updateDrawOrder(const sf::Drawable* drawable, DrawOrder drawOrder) {
  // find the element to update
  auto foundIt = std::ranges::find_if(
      drawEntries, [drawable](const DrawEntry& drawEntry) { return drawEntry.drawable == drawable; });
  assert(foundIt != drawEntries.end());
  // make an updated copy
  DrawEntry updatedDrawEntry = *foundIt;
  updatedDrawEntry.drawOrder = drawOrder;
  // check if it's still in the right place
  const auto& less = overdraw ? DrawEntry::lessOverdraw : DrawEntry::less;
  const bool isTooSmall = foundIt != drawEntries.begin() && less(updatedDrawEntry, *(foundIt - 1));
  const bool isTooBig = foundIt != drawEntries.end() - 1 && less(*(foundIt + 1), updatedDrawEntry);
  if (!isTooSmall && !isTooBig) {
    *foundIt = updatedDrawEntry;
    return;
  }
  // otherwise, move wrongly placed elements to where they should be and update the new slot
  if (isTooSmall) {
    // check between start and previous value
    auto newPos = std::upper_bound(drawEntries.begin(), foundIt, updatedDrawEntry, less);
    std::move_backward(newPos, foundIt, foundIt + 1);
    *newPos = updatedDrawEntry;
  } else if (isTooBig) {
    // check between previous value and end
    auto newPos = std::upper_bound(foundIt, drawEntries.end(), updatedDrawEntry, less);
    std::move(foundIt + 1, newPos, foundIt);
    *newPos = updatedDrawEntry;
  }
}

void RenderQueue::unregisterDrawable(const sf::Drawable* drawable) {
  std::erase_if(drawEntries, [drawable](const DrawEntry& drawEntry) { return drawEntry.drawable == drawable; });
}

void RenderQueue::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const auto& [drawable, _0, _1] : drawEntries) {
    assert(drawable);
    target.draw(*drawable, states);
  }
}

void RenderQueue::clear() {
  drawEntries.clear();
  std::ranges::sort(drawEntries, overdraw ? DrawEntry::lessOverdraw : DrawEntry::less);
}

void RenderQueue::setOverdraw(bool flag) {
  overdraw = flag;
}

bool RenderQueue::DrawEntry::less(const DrawEntry& _lhs, const DrawEntry& _rhs) {
  // no overdraw: by draw order first, then debug above
  return std::tie(_lhs.drawOrder, _lhs.isDebug) < std::tie(_rhs.drawOrder, _rhs.isDebug);
}

bool RenderQueue::DrawEntry::lessOverdraw(const DrawEntry& _lhs, const DrawEntry& _rhs) {
  // overdraw: debug above, then by draw order
  return std::tie(_lhs.isDebug, _lhs.drawOrder) < std::tie(_rhs.isDebug, _rhs.drawOrder);
}

}  // namespace loki::system