#include <loki/physics/materials/PhysicsMaterial.hpp>

namespace loki::physics {

b2SurfaceMaterial PhysicsMaterial::toSurfaceMaterialDef() const {
  b2SurfaceMaterial materialDef = b2DefaultSurfaceMaterial();
  materialDef.friction = friction;
  materialDef.restitution = restitution;
  materialDef.rollingResistance = rollingResistance;
  materialDef.tangentSpeed = tangentSpeed;
  return materialDef;
}

}  // namespace loki::physics
