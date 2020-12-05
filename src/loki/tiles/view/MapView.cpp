/*!
 * \file MapView.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "MapView.hpp"
#include <loki/common/IterAadapters.hpp>
#include "ObjectLayerView.hpp"
#include "TileLayerView.hpp"

namespace loki::tiles {

MapView::MapView(const MapData& data) {
  setData(data);
}

void MapView::setData(const MapData &data) {
  this->data = &data;
  for (const auto&& [i, layerData]: common::enumerate(data.layers)) {
    if (std::holds_alternative<TileLayerData>(layerData)) {
      layers.push_back(std::unique_ptr<LayerView>(new TileLayerView(*this, i)));
    } else if (std::holds_alternative<ObjectLayerData>(layerData)) {
      layers.push_back(std::unique_ptr<LayerView>(new ObjectLayerView(*this, i)));
    }
  }
  background.setSize({
      float(data.tilesets.at(0)->tileSize.x * data.gridSize.x),
      float(data.tilesets.at(0)->tileSize.y * data.gridSize.y),
  });
  background.setFillColor(data.backgroundColor);
}

void MapView::update(const sf::Time& delta) {
  for (auto& layer : layers) {
    layer->update(delta);
  }
}

}