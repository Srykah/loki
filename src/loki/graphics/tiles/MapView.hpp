#pragma once

#include <SFML/Graphics.hpp>
#include "MapData.hpp"

namespace loki::graphics {

class MapView : public sf::Drawable, public sf::Transformable {
 public:
  explicit MapView(const MapData& mapData);

  void draw(sf::RenderTarget& target, sf::RenderStates states = {}) const override;

 private:
  void init(const MapData& data);
  void fillVerticesForTile(size_t startIndex, size_t x, size_t y, const TileSetData& tileset, int tileIndex);

 private:
  sf::Texture texture;
  sf::Vector2u tilesetGridSize;
  sf::VertexArray vertexArray;
};

}