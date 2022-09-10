#include "MapView.hpp"

#include <loki/core/utils/IterAdapters.hpp>

#include "ObjectLayerView.hpp"
#include "TileLayerView.hpp"

namespace loki::gfx {

MapView::MapView(const MapData& data) {
  setData(data);
}

void MapView::setData(const MapData& data) {
  this->data = &data;
  for (const auto&& [i, layerData] : core::enumerate(data.layers)) {
    if (std::holds_alternative<TileLayerData>(layerData)) {
      layers.emplace_back(std::in_place_type_t<TileLayerView>{},
                          std::get<TileLayerData>(layerData),
                          *data.tilesets.at(0));
    } else if (std::holds_alternative<ObjectLayerData>(layerData)) {
      layers.emplace_back(std::in_place_type_t<ObjectLayerView>{},
                          std::get<ObjectLayerData>(layerData));
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

void MapView::drawLayer(std::size_t index,
                        sf::RenderTarget& target,
                        sf::RenderStates states) const {
  std::visit([&](auto&& layer) { target.draw(layer, states); },
             layers.at(index));
}

}  // namespace loki::gfx
