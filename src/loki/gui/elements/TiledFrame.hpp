#pragma once

#include <SFML/Graphics.hpp>
#include "Frame.hpp"
#include "loki/graphics/tiles/TilesetData.hpp"

namespace loki::gui {

class TiledFrame : public Frame {
 public:
  TiledFrame(const gfx::TilesetData& tileset);

  void draw(sf::RenderTarget& target,
            sf::RenderStates states = {}) const override;

 private:
  const gfx::TilesetData& tileset;
};

}  // namespace loki::gui
