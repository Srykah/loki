#include <loki/physics/materials/PhysicsFilter.hpp>

namespace loki::physics {

b2Filter PhysicsFilter::toFilterDef() const {
  b2Filter filterDef = b2DefaultFilter();
  filterDef.categoryBits = categoryBits;
  filterDef.maskBits = maskBits;
  filterDef.groupIndex = groupIndex;
  return filterDef;
}

}  // namespace loki::physics
