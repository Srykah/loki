#pragma once

#include <SFML/Graphics.hpp>

#include <loki/tiles/TileMapData.hpp>

namespace loki::graphics {

class GraphicsTileMap : public sf::Drawable, public sf::Transformable {
 public:
  void setData(const tiles::TileMapData& mapData);

  void draw(sf::RenderTarget& target, sf::RenderStates states = {}) const override;

 private:
  void fillVerticesForTile(size_t startIndex, size_t x, size_t y, sf::Vector2f tileSize, int tileIndex);

 private:
  const sf::Texture* texture = nullptr;
  sf::Vector2u tilesetGridSize;
  sf::VertexArray vertexArray;
};

}  // namespace loki::graphics