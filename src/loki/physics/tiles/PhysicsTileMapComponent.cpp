#include "PhysicsTileMapComponent.hpp"

#include <ranges>

#include <loki/system/scene/SceneManager.hpp>
#include <loki/physics/tiles/CollisionTileAttribute.hpp>
#include <loki/physics/world/PhysicsWorldComponent.hpp>
#include <loki/tiles/TileMapDataComponent.hpp>

#include "loki/core/math/Vector2Ops.hpp"
#include "loki/physics/utils/conversions.hpp"

namespace loki::physics {

void PhysicsTileMapComponent::onStartInit() {
  auto* dataComp = getActor().getComponent<tiles::TileMapDataComponent>();
  assert(dataComp);
  addResources(dataComp->getDataHandle());
}

void PhysicsTileMapComponent::onFinalizeInit() {
  auto* dataComp = getActor().getComponent<tiles::TileMapDataComponent>();
  assert(dataComp);
  createShapes(dataComp->getDataHandle().getData());
  body.setTransformable(getActor().getTransformable());  // init position and rotation
}

system::DrawOrder PhysicsTileMapComponent::getDebugDrawOrder() const {
  return {};
}

void PhysicsTileMapComponent::debugDraw(sf::RenderTarget& target, sf::RenderStates states) const {
  body.debugDraw(target, states);
}

void PhysicsTileMapComponent::createShapes(const tiles::TileMapData& data) {
  body = getService<system::SceneManager>()
             .getCurrentScene()
             ->getRoot()
             .getComponent<PhysicsWorldComponent>()
             ->getWorld()
             ->createBody(auto{bodyParams});
  const auto* tileSizeAttr = data.tileset->getTileSetAttribute<tiles::SizeTileSetAttribute>();
  assert(tileSizeAttr);
  sf::Vector2f tileSize = tileSizeAttr->tileSize;
  const float pixelsToMeters = body.getWorld()->getPixelsToMetersRatio();
  auto halfTileSizeInMeters = tileSize * 0.5f / pixelsToMeters;
  for (auto&& [i, tileIndex] : data.tiles | std::views::enumerate) {
    const auto* collTileAttr = data.tileset->getTileAttribute<CollisionTileAttribute>(tileIndex);
    if (!collTileAttr || !collTileAttr->isSolid)
      continue;
    auto coordsInTiles = core::getCoordsFromIndex<float>(i, data.mapSize.x);
    coordsInTiles += {0.5f, 0.5f};
    auto coordsInPixels = core::compMult(coordsInTiles, tileSize);
    auto coordsInMeters = coordsInPixels / pixelsToMeters;
    PhysicsFixtureParams fixtureParams = collTileAttr->fixtureParams;
    auto boxParams = std::make_shared<PolygonShapeParams>();
    boxParams->polygonShape.SetAsBox(halfTileSizeInMeters.x, halfTileSizeInMeters.y, toB2Vec2(coordsInMeters), 0.f);
    fixtureParams.shapeParams = std::move(boxParams);
    body.createFixture(auto{fixtureParams});
  }
}

}  // namespace loki::physics
