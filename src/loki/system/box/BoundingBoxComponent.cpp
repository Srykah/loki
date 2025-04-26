#include "BoundingBoxComponent.hpp"

#include <ecs/ComponentTraits.hpp>

namespace loki::system {

namespace {

void grow(sf::FloatRect& inOut, const sf::FloatRect& in) {
  sf::Vector2f min{std::min(inOut.left, in.left), std::min(inOut.top, in.top)};
  sf::Vector2f max{
      std::max(inOut.left + inOut.width, in.left + in.width),
      std::max(inOut.top + inOut.height, in.top + in.height),
  };
  inOut.left = min.x;
  inOut.top = min.y;
  inOut.width = max.x - min.x;
  inOut.height = max.y - min.y;
}

}  // namespace

void BoundingBoxComponent::onUpdate(sf::Time delta) {
  // if (!isDirty)
  //   return;

  auto filter = [](const BaseComponentTraits& compTraits) { return compTraits.hasBoundingBox(); };
  auto visitor = [&](const BaseComponentTraits& compTraits, void* comp) {
    grow(localBox, compTraits.getBoundingBox(comp));
  };
  getActor().visitComponents(filter, visitor);
  auto globalTransform = getGlobalTransform();
  globalBox = globalTransform.transformRect(localBox);
  isDirty = false;
}

void BoundingBoxComponent::onDebugDraw(sf::Time delta) {}

}  // namespace loki::system
