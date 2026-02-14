#include "PhysicsTileMapComponent.hpp"

#include <ranges>

#include <render/RendererModule.hpp>

#include <loki/system/scene/SceneManager.hpp>
#include <loki/physics/tiles/CollisionTileAttribute.hpp>
#include <loki/physics/world/PhysicsWorldComponent.hpp>
#include <loki/tiles/TileMapDataComponent.hpp>

#include "loki/core/math/Vector2Ops.hpp"
#include "loki/physics/utils/conversions.hpp"

namespace loki::physics {

void PhysicsTileMapComponent::onBeginInit() {
  auto* dataComp = getActor().getComponent<tiles::TileMapDataComponent>();
  assert(dataComp);
  addResources(dataComp->getDataHandle());
}

void PhysicsTileMapComponent::onEndInit() {
  auto* dataComp = getActor().getComponent<tiles::TileMapDataComponent>();
  assert(dataComp);
  createShapes(dataComp->getDataHandle().getData());
  body.setTransformable(getActor().getTransformable());  // init position and rotation
}

void PhysicsTileMapComponent::createShapes(const tiles::TileMapData& data) {
  body = getService<system::SceneManager>()
             .getCurrentScene()
             ->getRoot()
             .getComponent<PhysicsWorldComponent>()
             ->getWorld()
             ->createBody(PhysicsBodyParams{bodyParams});
  const auto* tileSizeAttr = data.tileset->getTileSetAttribute<tiles::SizeTileSetAttribute>();
  assert(tileSizeAttr);
  sf::Vector2f tileSize = tileSizeAttr->tileSize;
  const float pixelsToMeters = body.getWorld()->getPixelsToMetersRatio();
  auto halfTileSizeInMeters = tileSize * 0.5f / pixelsToMeters;
  for (std::size_t i{0}; i < data.tiles.size(); ++i) {
    int tileIndex = data.tiles[i];
    const auto* collTileAttr = data.tileset->getTileAttribute<CollisionTileAttribute>(tileIndex);
    if (!collTileAttr || !collTileAttr->isSolid)
      continue;
    auto coordsInTiles = core::getCoordsFromIndex<float>(i, data.mapSize.x);
    coordsInTiles += {0.5f, 0.5f};
    auto coordsInPixels = core::compMult(coordsInTiles, tileSize);
    auto coordsInMeters = coordsInPixels / pixelsToMeters;
    sf::Transformable shapeTrs;
    shapeTrs.setPosition(coordsInMeters);
    body.createShape(*collTileAttr->shapeParams, shapeTrs);
  }
}

sf::FloatRect PhysicsTileMapComponent::getBoundingBox() const {
  return body.getBoundingBox();
}

}  // namespace loki::physics
