#include "GraphicsTileMap.hpp"

#include <array>

#include <loki/core/math/Vector2Ops.hpp>
#include <loki/graphics/tiles/TextureTileSetAttribute.hpp>

namespace loki::graphics {

namespace {
constexpr size_t VERTICES_PER_TILE = 6;  // two triangles per tile
}

void GraphicsTileMap::setData(const tiles::TileMapData& mapData) {
  const tiles::TileSetData& tileSetData = mapData.tileset.getData();
  if (auto* graphicsTileSetAttr = tileSetData.getTileSetAttribute<TextureTileSetAttribute>())
    texture = &graphicsTileSetAttr->texture.getData();
  else
    return;
  sf::Vector2f tileSize;
  if (auto* sizeTileSetAttr = tileSetData.getTileSetAttribute<tiles::SizeTileSetAttribute>())
    tileSize = sizeTileSetAttr->tileSize;
  else
    return;
  tilesetGridSize = sf::Vector2u{core::compDiv(texture->getSize(), tileSize)};
  vertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
  vertexArray.resize(VERTICES_PER_TILE * mapData.tiles.size());
  size_t i = 0;
  for (size_t y = 0; y < mapData.mapSize.y; ++y) {
    for (size_t x = 0; x < mapData.mapSize.x; ++x) {
      int tileIndex = mapData.tiles[i];
      fillVerticesForTile(i * VERTICES_PER_TILE, x, y, tileSize, tileIndex);
      ++i;
    }
  }
}

void GraphicsTileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  states.texture = texture;
  target.draw(vertexArray, states);
}

void GraphicsTileMap::fillVerticesForTile(size_t startIndex, size_t x, size_t y, sf::Vector2f tileSize, int tileIndex) {
  //  0 ------ 1/4
  //  |      /  |
  //  |    /    |
  //  |  /      |
  // 2/3 ------ 5

  const std::array<sf::Vector2f, VERTICES_PER_TILE> offsets{{
      {0.f, 0.f},
      {tileSize.x, 0.f},
      {0.f, tileSize.y},
      {0.f, tileSize.y},
      {tileSize.x, 0.f},
      tileSize,
  }};

  const sf::Vector2f startPos{x * tileSize.x, y * tileSize.y};
  const sf::Vector2f startTexCoords{static_cast<float>(tileIndex % tilesetGridSize.x) * tileSize.x,
                                    static_cast<float>(tileIndex / tilesetGridSize.x) * tileSize.y};

  for (size_t i = 0; i < VERTICES_PER_TILE; ++i) {
    vertexArray[startIndex + i].position = startPos + offsets[i];
    vertexArray[startIndex + i].texCoords = startTexCoords + offsets[i];
  }
}

}  // namespace loki::graphics