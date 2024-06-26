#pragma once

#include <variant>

#include <SFML/Graphics.hpp>

#include "ObjectLayerView.hpp"
#include "TileLayerView.hpp"
#include <loki/graphics/tiles/MapData.hpp>

namespace loki::graphics {

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

}  // namespace loki::graphics
