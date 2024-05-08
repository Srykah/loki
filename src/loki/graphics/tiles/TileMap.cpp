#include "TileMap.hpp"

#include <array>

namespace loki::graphics {

namespace {
constexpr size_t VERTICES_PER_TILE = 6;  // two triangles per tile
}

void TileMap::setData(const TileMapData& mapData) {
  const TileSetData& tileSetData = mapData.tileset.getData();
  texture = &tileSetData.texture.getData();
  tilesetGridSize.x = texture->getSize().x / tileSetData.tileSize.x;
  tilesetGridSize.y = texture->getSize().y / tileSetData.tileSize.y;
  vertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
  vertexArray.resize(VERTICES_PER_TILE * mapData.tiles.size());
  size_t i = 0;
  for (size_t y = 0; y < mapData.mapSize.y; ++y) {
    for (size_t x = 0; x < mapData.mapSize.x; ++x) {
      int tileIndex = mapData.tiles[i];
      fillVerticesForTile(i * VERTICES_PER_TILE, x, y, tileSetData, tileIndex);
      ++i;
    }
  }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  states.texture = texture;
  target.draw(vertexArray, states);
}

void TileMap::fillVerticesForTile(size_t startIndex, size_t x, size_t y, const TileSetData& tileset, int tileIndex) {
  //  0 ------ 1/4
  //  |      /  |
  //  |    /    |
  //  |  /      |
  // 2/3 ------ 5

  const sf::Vector2f tileSize{tileset.tileSize};

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