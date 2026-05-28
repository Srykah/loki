#include <algorithm>

#include <loki/core/math/Misc.hpp>
#include <loki/physics/shapes/PhysicsShapeParams.hpp>
#include <loki/physics/utils/conversions.hpp>

namespace loki::physics {

namespace {
float getUniformScaling(const sf::Transform& trs) {
  const auto transformedX = trs.transformPoint({1.f, 0.f});
  return std::sqrt(transformedX.x * transformedX.x + transformedX.y * transformedX.y);
}
b2Vec2 getCenter(const sf::Transform& trs) {
  return toB2Vec2(trs.transformPoint({0.f, 0.f}));
}
}  // namespace

b2ShapeDef PhysicsShapeParams::toShapeDef() const {
  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.material = material.toSurfaceMaterialDef();
  shapeDef.density = density;
  shapeDef.filter = filter.toFilterDef();
  shapeDef.isSensor = isSensor;
  shapeDef.enableSensorEvents = enableSensorEvents;
  shapeDef.enableContactEvents = enableContactEvents;
  shapeDef.enableHitEvents = enableHitEvents;
  shapeDef.enablePreSolveEvents = enablePreSolveEvents;
  shapeDef.invokeContactCreation = invokeContactCreation;
  shapeDef.updateBodyMass = updateBodyMass;
  return shapeDef;
}

b2ShapeId CircleShapeParams::createShape(b2BodyId bodyId, const sf::Transformable& trs) const {
  const auto shapeDef = toShapeDef();
  const auto totalTrs = trs.getTransform() * offset.getTransform();
  const float uniformScaling = getUniformScaling(totalTrs);
  const b2Circle circleDef{
      .center = getCenter(totalTrs),
      .radius = uniformScaling * radius,
  };
  return b2CreateCircleShape(bodyId, &shapeDef, &circleDef);
}

b2ShapeId CapsuleShapeParams::createShape(b2BodyId bodyId, const sf::Transformable& trs) const {
  const auto shapeDef = toShapeDef();
  const auto totalTrs = trs.getTransform() * offset.getTransform();
  const float uniformScaling = getUniformScaling(totalTrs);
  const b2Capsule segmentDef{
      .center1 = toB2Vec2(totalTrs.transformPoint(center1)),
      .center2 = toB2Vec2(totalTrs.transformPoint(center2)),
      .radius = uniformScaling * radius,
  };
  return b2CreateCapsuleShape(bodyId, &shapeDef, &segmentDef);
}

b2ShapeId SegmentShapeParams::createShape(b2BodyId bodyId, const sf::Transformable& trs) const {
  const auto shapeDef = toShapeDef();
  const auto totalTrs = trs.getTransform() * offset.getTransform();
  const b2Segment segmentDef{
      .point1 = toB2Vec2(totalTrs.transformPoint(point1)),
      .point2 = toB2Vec2(totalTrs.transformPoint(point2)),
  };
  return b2CreateSegmentShape(bodyId, &shapeDef, &segmentDef);
}

b2ShapeId PolygonShapeParams::createShape(b2BodyId bodyId, const sf::Transformable& trs) const {
  const auto shapeDef = toShapeDef();
  const auto totalTrs = trs.getTransform() * offset.getTransform();
  const float uniformScaling = getUniformScaling(totalTrs);
  std::vector<b2Vec2> pointsDef(points.size());
  std::ranges::transform(points, pointsDef.begin(),
                         [&totalTrs](const sf::Vector2f& point) { return toB2Vec2(totalTrs.transformPoint(point)); });
  const b2Hull hullDef = b2ComputeHull(pointsDef.data(), pointsDef.size());
  const b2Polygon polygonDef = b2MakePolygon(&hullDef, uniformScaling * radius);
  return b2CreatePolygonShape(bodyId, &shapeDef, &polygonDef);
}

b2ShapeId BoxShapeParams::createShape(b2BodyId bodyId, const sf::Transformable& trs) const {
  const auto shapeDef = toShapeDef();
  const auto totalTrs = trs.getTransform() * offset.getTransform();
  const float uniformScaling = getUniformScaling(totalTrs);
  const b2Vec2 center = getCenter(totalTrs);
  const b2Rot rotation = b2MakeRot((trs.getRotation() + offset.getRotation()).asRadians());
  const b2Polygon polygonDef = b2MakeOffsetRoundedBox(uniformScaling * halfSize.x, uniformScaling * halfSize.y, center,
                                                      rotation, uniformScaling * radius);
  return b2CreatePolygonShape(bodyId, &shapeDef, &polygonDef);
}

b2ShapeId ChainShapeParams::createShape(b2BodyId bodyId, const sf::Transformable& trs) const {
  const auto totalTrs = trs.getTransform() * offset.getTransform();
  std::vector<b2Vec2> pointsDef(points.size());
  std::ranges::transform(points, pointsDef.begin(),
                         [&totalTrs](const sf::Vector2f& point) { return toB2Vec2(totalTrs.transformPoint(point)); });
  const b2SurfaceMaterial materialDef = material.toSurfaceMaterialDef();
  b2ChainDef chainDef = b2DefaultChainDef();
  chainDef.points = pointsDef.data();
  chainDef.count = pointsDef.size();
  chainDef.materials = &materialDef;
  chainDef.materialCount = 1;
  chainDef.filter = filter.toFilterDef();
  chainDef.isLoop = isLoop;
  chainDef.enableSensorEvents = enableSensorEvents;
  static_assert(requires { B2_ID_EQUALS(b2ShapeId{}, b2ChainId{}); });  // size check is done in bitcast
  return std::bit_cast<b2ShapeId>(b2CreateChain(bodyId, &chainDef));
}

}  // namespace loki::physics