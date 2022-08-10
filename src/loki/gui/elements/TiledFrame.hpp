/*!
 * \file TiledFrame.hpp.h
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include "Frame.hpp"
#include "loki/graphics/tiles/TilesetData.hpp"

namespace loki::gui {

class TiledFrame : public Frame {
 public:
  TiledFrame(const tiles::TilesetData& tileset);

  void draw(sf::RenderTarget& target,
            sf::RenderStates states = {}) const override;

 private:
  const tiles::TilesetData& tileset;
};

}  // namespace loki::gui
