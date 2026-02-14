#include <math/Misc.hpp>
#include <utils/conversions.hpp>

#include <loki/physics/shapes/PhysicsShapeParams.hpp>

namespace loki::physics {

b2ShapeId CircleShapeParams::createShape(b2BodyId bodyId) const {
  const auto shapeDef = toShapeDef();
  const float uniformScaling = offset.getScale().x;
  const b2Circle circleDef {
    .center = toB2Vec2(uniformScaling * (offset.getPosition() - offset.getOrigin())),
    .radius = uniformScaling * radius,
  };
  return b2CreateCircleShape(bodyId, &shapeDef, &circleDef);
}

b2ShapeId CapsuleShapeParams::createShape(b2BodyId bodyId) const {
  const auto shapeDef = toShapeDef();
  const float uniformScaling = offset.getScale().x;
  const b2Capsule segmentDef {
    .center1 = toB2Vec2(offset.getTransform().transformPoint(center1)),
    .center2 = toB2Vec2(offset.getTransform().transformPoint(center2)),
    .radius = uniformScaling * radius,
  };
  return b2CreateCapsuleShape(bodyId, &shapeDef, &segmentDef);
}

b2ShapeId SegmentShapeParams::createShape(b2BodyId bodyId) const {
  const auto shapeDef = toShapeDef();
  const b2Segment segmentDef {
    .point1 = toB2Vec2(offset.getTransform().transformPoint(point1)),
    .point2 = toB2Vec2(offset.getTransform().transformPoint(point2)),
  };
  return b2CreateSegmentShape(bodyId, &shapeDef, &segmentDef);
}

b2ShapeId PolygonShapeParams::createShape(b2BodyId bodyId) const {
  const auto shapeDef = toShapeDef();
  const float uniformScaling = offset.getScale().x;
  std::vector<b2Vec2> pointsDef(points.size());
  std::ranges::transform(points, pointsDef.begin(), [&trs = offset.getTransform()](const sf::Vector2f& point) {
    return toB2Vec2(trs.transformPoint(point));
  });
  const b2Hull hullDef = b2ComputeHull(pointsDef.data(), pointsDef.size());
  const b2Polygon polygonDef = b2MakePolygon(&hullDef, uniformScaling * radius);
  return b2CreatePolygonShape(bodyId, &shapeDef, &polygonDef);
}

b2ShapeId BoxShapeParams::createShape(b2BodyId bodyId) const {
  const auto shapeDef = toShapeDef();
  const float uniformScaling = offset.getScale().x;
  const b2Vec2 center = toB2Vec2(uniformScaling * (offset.getPosition() - offset.getOrigin()));
  const b2Rot rotation = b2MakeRot(core::toRadians(offset.getRotation()));
  const b2Polygon polygonDef = b2MakeOffsetRoundedBox(uniformScaling * halfSize.x, uniformScaling * halfSize.y, center, rotation, uniformScaling * radius);
  return b2CreatePolygonShape(bodyId, &shapeDef, &polygonDef);
}

b2ShapeId ChainShapeParams::createShape(b2BodyId bodyId) const {
  std::vector<b2Vec2> pointsDef(points.size());
  std::ranges::transform(points, pointsDef.begin(), [&trs = offset.getTransform()](const sf::Vector2f& point) {
    return toB2Vec2(trs.transformPoint(point));
  });
  const b2SurfaceMaterial materialDef = material.toSurfaceMaterialDef();
  b2ChainDef chainDef = b2DefaultChainDef();
  chainDef.points = pointsDef.data();
  chainDef.count = pointsDef.size();
  chainDef.materials = &materialDef;
  chainDef.materialCount = 1;
  chainDef.filter = filter.toFilterDef();
  chainDef.isLoop = isLoop;
  chainDef.enableSensorEvents = enableSensorEvents;
  static_assert(requires { B2_ID_EQUALS(b2ShapeId{}, b2ChainId{}); }); // size check is done in bitcast
  return std::bit_cast<b2ShapeId>(b2CreateChain(bodyId, &chainDef));
}

}  // namespace loki::physics