#include "TileLayerView.hpp"

#include "MapView.hpp"

namespace loki::graphics {

TileLayerView::TileLayerView(const TileLayerData& layerData,
                             const TilesetData& tilesetData)
    : vertices(sf::Quads), layerData(layerData), tilesetData(tilesetData) {
  initGrid();
}

void TileLayerView::initGrid() {
  vertices.resize(layerData.data.getWidth() * layerData.data.getHeight() * 4);
  for (auto y{0u}; y < layerData.data.getHeight(); ++y) {
    for (auto x{0u}; x < layerData.data.getWidth(); ++x) {
      initVertices(x, y);

      auto tileId = layerData.data[{x, y}] - 1;
      if (tileId == -1) {
        setTileTransparent(x, y);
      } else if (tilesetData.tiles.count(tileId) &&
                 !tilesetData.tiles.at(tileId).animation.empty()) {
        animatedTiles.emplace(tileId, AnimatedTile{
                                          0,
                                          sf::Time::Zero,
                                      });
        setTile(x, y, tilesetData.tiles.at(tileId).animation.at(0).tileid);
      } else {
        setTile(x, y, tileId);
      }
    }
  }
}

void TileLayerView::update(const sf::Time& delta) {
  for (auto&& [gid, tile] : animatedTiles) {
    const auto& animData = tilesetData.tiles.at(gid).animation;
    bool needUpdate = false;
    tile.timeSinceLastFrame += delta;
    while (tile.timeSinceLastFrame >= animData.at(tile.curFrame).duration) {
      tile.timeSinceLastFrame -= animData.at(tile.curFrame).duration;
      tile.curFrame = (tile.curFrame + 1) % animData.size();
      needUpdate = true;
    }
    if (needUpdate) {
      for (int x{0}; x < layerData.data.getWidth(); ++x) {
        for (int y{0}; y < layerData.data.getHeight(); ++y) {
          if (layerData.data[{x, y}] - 1 == gid) {
            setTile(x, y, animData.at(tile.curFrame).tileid);
          }
        }
      }
    }
  }
}

void TileLayerView::draw(sf::RenderTarget& target,
                         sf::RenderStates states) const {
  states.transform *= getTransform();
  states.texture = &tilesetData.texture.getData();
  target.draw(vertices, states);
}

void TileLayerView::initVertices(unsigned int x, unsigned int y) {
  auto tileWidth = tilesetData.tileSize.x;
  auto tileHeight = tilesetData.tileSize.y;
  auto i{(x + layerData.data.getWidth() * y) * 4};
  auto tilePositionOrigin = sf::Vector2f(tileWidth * x, tileHeight * y);

  vertices[i].position = tilePositionOrigin;
  vertices[i + 1].position = tilePositionOrigin + sf::Vector2f(tileWidth, 0.f);
  vertices[i + 2].position =
      tilePositionOrigin + sf::Vector2f(tileWidth, tileHeight);
  vertices[i + 3].position = tilePositionOrigin + sf::Vector2f(0.f, tileHeight);
}

void TileLayerView::setTile(int x, int y, int tileId) {
  auto i{(x + layerData.data.getWidth() * y) * 4};
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
  auto i{(x + layerData.data.getWidth() * y) * 4};
  vertices[i].color = sf::Color::Transparent;
  vertices[i + 1].color = sf::Color::Transparent;
  vertices[i + 2].color = sf::Color::Transparent;
  vertices[i + 3].color = sf::Color::Transparent;
}

}  // namespace loki::graphics
