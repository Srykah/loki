/*!
 * \file ObjectLayerView.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "ObjectLayerView.hpp"

namespace loki::tiles {

ObjectLayerView::ObjectLayerView(const ObjectLayerData& data)
    : layerData(data) {
  initObjects();
}

void ObjectLayerView::draw(sf::RenderTarget& target,
                           sf::RenderStates states) const {
  states.transform *= getTransform();
  for (const auto& object : objects) {
    target.draw(*object, states);
  }
}

void ObjectLayerView::initObjects() {
  /*
  for (const auto& objectData : layerData.objects) {
    if (std::holds_alternative<TileObjectData>(objectData)) {
      const auto& tileObjectData = std::get<TileObjectData>(objectData);
      const auto& tilesetData = *parent.getData().tilesets.at(0);
      auto tile = std::make_unique<sf::Sprite>();
      tile->setTexture(tilesetData.texture);
      if (tilesetData.tiles.count(tileObjectData.globalTileId-1)) {
        tile->setTextureRect(sf::IntRect {

        })
      }
      tile->setTextureRect(tilesetData)
      objects.emplace_back();

    }
  }*/
}

}  // namespace loki::tiles
