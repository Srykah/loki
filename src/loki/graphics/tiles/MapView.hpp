/*!
 * \file MapView.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <variant>
#include "ObjectLayerView.hpp"
#include "TileLayerView.hpp"
#include "loki/graphics/tiles/MapData.hpp"

namespace loki::tiles {

using LayerView = std::variant<ObjectLayerView, TileLayerView>;

class MapView : public sf::Transformable {
 public:
  MapView() = default;
  explicit MapView(const MapData& data);

  void setData(const MapData& data);
  const MapData& getData() const { return *data; }

  void update(sf::Time delta);

  const std::vector<LayerView>& getLayers() const { return layers; }
  const LayerView& getLayer(std::size_t index) const {
    return layers.at(index);
  }
  void drawLayer(std::size_t index,
                 sf::RenderTarget& target,
                 sf::RenderStates states = {}) const;

  const sf::RectangleShape& getBackground() const { return background; }

 private:
  const MapData* data = nullptr;
  std::vector<LayerView> layers;
  sf::RectangleShape background;
};

}  // namespace loki::tiles
