#include "MapView.hpp"

#include <array>

namespace loki::graphics {

namespace {
constexpr size_t VERTICES_PER_TILE = 6; // two triangles per tile
}

MapView::MapView(const MapData& mapData) {
  texture.loadFromFile(mapData.tileset.texturePath.string());
  tilesetGridSize.x = texture.getSize().x / mapData.tileset.tileSize.x;
  tilesetGridSize.y = texture.getSize().y / mapData.tileset.tileSize.y;
  init(mapData);
}

void MapView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  states.texture = &texture;
  target.draw(vertexArray, states);
}

void MapView::init(const MapData& data) {
  vertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
  vertexArray.resize(VERTICES_PER_TILE * data.tiles.size());
  size_t i = 0;
  for (size_t y = 0; y < data.mapSize.y; ++y) {
    for (size_t x = 0; x < data.mapSize.x; ++x) {
      int tileIndex = data.tiles[i];
      fillVerticesForTile(i * VERTICES_PER_TILE, x, y, data.tileset, tileIndex);
      ++i;
    }
  }
}

void MapView::fillVerticesForTile(size_t startIndex, size_t x, size_t y, const TileSetData& tileset, int tileIndex) {
  //  0 ------ 1/4
  //  |      /  |
  //  |    /    |
  //  |  /      |
  // 2/3 ------ 5

  const sf::Vector2f tileSize{tileset.tileSize};

  const std::array<sf::Vector2f, VERTICES_PER_TILE> offsets {{
    { 0.f, 0.f },
    { tileSize.x, 0.f },
    { 0.f, tileSize.y },
    { 0.f, tileSize.y },
    { tileSize.x, 0.f },
    tileSize,
  }};

  const sf::Vector2f startPos{x * tileSize.x, y * tileSize.y};
  const sf::Vector2f startTexCoords{
      static_cast<float>(tileIndex % tilesetGridSize.x) * tileSize.x,
      static_cast<float>(tileIndex / tilesetGridSize.x) * tileSize.y};

  for (size_t i = 0; i < VERTICES_PER_TILE; ++i) {
    vertexArray[startIndex + i].position = startPos + offsets[i];
    vertexArray[startIndex + i].texCoords = startTexCoords + offsets[i];
  }
}

}