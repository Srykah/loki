/*!
 * \file MapView.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "MapView.hpp"
#include <loki/core/utils/IterAdapters.hpp>
#include "ObjectLayerView.hpp"
#include "TileLayerView.hpp"

namespace loki::tiles {

MapView::MapView(const MapData& data) {
  setData(data);
}

void MapView::setData(const MapData &data) {
  this->data = &data;
  for (const auto&& [i, layerData]: enumerate(data.layers)) {
    if (std::holds_alternative<TileLayerData>(layerData)) {
      layers.emplace_back(TileLayerView{std::get<TileLayerData>(layerData),
                                        *data.tilesets.at(0)});
    } else if (std::holds_alternative<ObjectLayerData>(layerData)) {
      layers.emplace_back(
          ObjectLayerView{std::get<ObjectLayerData>(layerData)});
    }
  }
  background.setSize({
      float(data.tilesets.at(0)->tileSize.x * data.gridSize.x),
      float(data.tilesets.at(0)->tileSize.y * data.gridSize.y),
  });
  background.setFillColor(data.backgroundColor);
}

void MapView::update(sf::Time delta) {
  for (auto& layer : layers) {
    std::visit([delta](auto&& l) { l.update(delta); }, layer);
  }
}

}
