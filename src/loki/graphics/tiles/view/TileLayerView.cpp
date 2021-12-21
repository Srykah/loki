/*!
 * \file LayerView.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TileLayerView.hpp"
#include "MapView.hpp"

namespace loki::tiles {

TileLayerView::TileLayerView(const MapView& parent, int layerId)
    : LayerView(parent),
      vertices(sf::Quads),
      layerData(std::get<TileLayerData>(parent.getData().layers.at(layerId))),
      gridSize(parent.getData().gridSize),
      tilesetData(*parent.getData().tilesets.at(0)) {
  vertices.resize(gridSize.x * gridSize.y * 4);
  for (auto y{0u}; y < gridSize.y; ++y) {
    for (auto x{0u}; x < gridSize.x; ++x) {
      initVertices(x, y);

      auto tileId = layerData.data[{x, y}] - 1;
      if (tileId == -1) {
        setTileTransparent(x, y);
      } else if (tilesetData.tiles.count(tileId) &&
                 !tilesetData.tiles.at(tileId).animation.empty()) {
        tileViewData.emplace(tileId, TileViewData{
                                         0,
                                         sf::Time::Zero,
                                     });
        setTile(x, y, tilesetData.tiles.at(tileId).animation.at(0).tileId);
      } else {
        setTile(x, y, tileId);
      }
    }
  }
}

void TileLayerView::update(const sf::Time& delta) {
  for (auto&& [tileId, tileViewDatum] : tileViewData) {
    const auto& tileData = tilesetData.tiles.at(tileId);
    bool needUpdate = false;
    tileViewDatum.timeSinceLastFrame += delta;
    while (tileViewDatum.timeSinceLastFrame >=
           tileData.animation.at(tileViewDatum.frameIndex).duration) {
      tileViewDatum.timeSinceLastFrame -=
          tileData.animation.at(tileViewDatum.frameIndex).duration;
      tileViewDatum.frameIndex =
          (tileViewDatum.frameIndex + 1) % tileData.animation.size();
      needUpdate = true;
    }
    if (needUpdate) {
      for (int x{0}; x < gridSize.x; ++x) {
        for (int y{0}; y < gridSize.y; ++y) {
          if (layerData.data[{x, y}] - 1 == tileId) {
            setTile(x, y,
                    tileData.animation.at(tileViewDatum.frameIndex).tileId);
          }
        }
      }
    }
  }
}

void TileLayerView::draw(sf::RenderTarget& target,
                         sf::RenderStates states) const {
  states.transform *= getParentTransform();
  states.texture = &tilesetData.texture;
  target.draw(vertices, states);
}

void TileLayerView::initVertices(unsigned int x, unsigned int y) {
  auto tileWidth = tilesetData.tileSize.x;
  auto tileHeight = tilesetData.tileSize.y;
  auto i{(x + gridSize.x * y) * 4};
  auto tilePositionOrigin = sf::Vector2f(tileWidth * x, tileHeight * y);

  vertices[i].position = tilePositionOrigin;
  vertices[i + 1].position = tilePositionOrigin + sf::Vector2f(tileWidth, 0.f);
  vertices[i + 2].position =
      tilePositionOrigin + sf::Vector2f(tileWidth, tileHeight);
  vertices[i + 3].position = tilePositionOrigin + sf::Vector2f(0.f, tileHeight);
}

void TileLayerView::setTile(int x, int y, int tileId) {
  auto i{(x + gridSize.x * y) * 4};
  auto tileWidth = tilesetData.tileSize.x;
  auto tileHeight = tilesetData.tileSize.y;
  auto tileTexCoordsOrigin =
      sf::Vector2f((tileId % tilesetData.dimensions.x) * tileWidth,
                   (tileId / tilesetData.dimensions.x) * tileHeight);

  vertices[i].texCoords = tileTexCoordsOrigin;
  vertices[i + 1].texCoords =
      tileTexCoordsOrigin + sf::Vector2f(tileWidth, 0.f);
  vertices[i + 2].texCoords =
      tileTexCoordsOrigin + sf::Vector2f(tileWidth, tileHeight);
  vertices[i + 3].texCoords =
      tileTexCoordsOrigin + sf::Vector2f(0.f, tileHeight);
}

void TileLayerView::setTileTransparent(unsigned int x, unsigned int y) {
  auto i{(x + gridSize.x * y) * 4};
  vertices[i].color = sf::Color::Transparent;
  vertices[i + 1].color = sf::Color::Transparent;
  vertices[i + 2].color = sf::Color::Transparent;
  vertices[i + 3].color = sf::Color::Transparent;
}

}  // namespace loki::tiles