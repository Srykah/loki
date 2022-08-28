#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>
#include <vector>
#include "loki/graphics/tiles/LayerData.hpp"

namespace loki::gfx {

class ObjectLayerView : public sf::Drawable, public sf::Transformable {
 public:
  explicit ObjectLayerView(const ObjectLayerData& data);

  ObjectLayerView(ObjectLayerView&) = delete;
  ObjectLayerView(ObjectLayerView&&) = default;

  void draw(sf::RenderTarget& target,
            sf::RenderStates states = sf::RenderStates()) const override;
  void update(const sf::Time& delta) {}

 private:
  void initObjects();

 private:
  const ObjectLayerData& layerData;
  std::vector<std::unique_ptr<sf::Drawable>> objects;
};

}  // namespace loki::gfx
