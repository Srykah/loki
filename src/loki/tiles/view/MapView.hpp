/*!
 * \file MapView.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include "loki/tiles/model/MapData.hpp"

namespace loki::tiles {
class LayerView;
class MapView : public sf::Transformable {
 public:
  MapView() = default;
  explicit MapView(const MapData& data);

  void setData(const MapData& data);
  const MapData& getData() const { return *data; }

  void update(const sf::Time& delta);

  const std::vector<std::unique_ptr<LayerView>>& getLayers() const {
    return layers;
  }
  const LayerView& getLayer(std::size_t index) const {
    return *layers.at(index);
  }

  const sf::RectangleShape& getBackground() const {
    return background;
  }

 private:
  const MapData* data = nullptr;
  std::vector<std::unique_ptr<LayerView>> layers;
  sf::RectangleShape background;
};

}  // namespace loki::tiles
