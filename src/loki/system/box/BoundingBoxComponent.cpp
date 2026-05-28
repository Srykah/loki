#include "BoundingBoxComponent.hpp"

#include <loki/core/math/Vector2Ops.hpp>
#include <loki/system/ecs/ComponentTraits.hpp>

namespace loki::system {

namespace {

void grow(sf::FloatRect& inOut, const sf::FloatRect& in) {
  const auto min = core::compMin(inOut.position, in.position);
  const auto max = core::compMax(inOut.position + inOut.size, in.position + in.size);
  inOut = {min, max - min};
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

}  // namespace loki::system
