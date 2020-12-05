/*!
 * \file LayerView.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <loki/common/Matrix.hpp>
#include <loki/tiles/model/TileLayerData.hpp>
#include <loki/tiles/model/TilesetData.hpp>

#include "LayerView.hpp"

namespace loki::tiles {
class MapView;

class TileLayerView : public LayerView {
 private:
  struct TileViewData {
    int frameIndex;
    sf::Time timeSinceLastFrame;
  };

 private:
  TileLayerView(const MapView& parent, int layerId);
  friend class MapView;

 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const override;
  void update(const sf::Time& delta);

 private:
  void initVertices(unsigned int x, unsigned int y);
  void setTile(int x, int y, int tileId);

 private:
  const TileLayerData& layerData;
  sf::Vector2u gridSize;
  const TilesetData& tilesetData;
  sf::VertexArray vertices;
  std::map<int, TileViewData> tileViewData;

 private:
  void setTileTransparent(unsigned int x, unsigned int y);
};
}  // namespace loki::tiles