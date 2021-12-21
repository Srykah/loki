/*!
 * \file ObjectLayerView.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include <vector>
#include "LayerView.hpp"

namespace loki::tiles {

class ObjectLayerView : public LayerView {
 private:
  ObjectLayerView(const MapView& parent, int layerId);
  friend class MapView;

 public:
  void draw(sf::RenderTarget& target,
            sf::RenderStates states = sf::RenderStates()) const override;
  void update(const sf::Time& delta) override{};

 private:
  const ObjectLayerData& layerData;
  std::vector<std::unique_ptr<sf::Drawable>> objects;

 private:
  void initObjects();
};

}  // namespace loki::tiles
