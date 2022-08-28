#pragma once

#include <SFML/Graphics.hpp>
#include <loki/core/utils/Matrix.hpp>
#include "loki/graphics/tiles/LayerData.hpp"
#include "loki/graphics/tiles/TilesetData.hpp"

namespace loki::gfx {

class TileLayerView : public sf::Drawable, public sf::Transformable {
 private:
  struct AnimatedTile {
    int curFrame = 0;
    sf::Time timeSinceLastFrame;
  };

 public:
  explicit TileLayerView(const TileLayerData& layerData,
                         const TilesetData& tilesetData);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  void update(const sf::Time& delta);

 private:
  void initGrid();
  void initVertices(unsigned int x, unsigned int y);
  void setTile(int x, int y, int tileId);
  void setTileTransparent(unsigned int x, unsigned int y);

 private:
  const TileLayerData& layerData;
  const TilesetData& tilesetData;
  sf::VertexArray vertices;
  std::map<int, AnimatedTile> animatedTiles;
};

}  // namespace loki::gfx
