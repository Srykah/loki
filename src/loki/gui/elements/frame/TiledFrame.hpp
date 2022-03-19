/*!
 * \file TiledFrame.hpp.h
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <loki/graphics/tiles/model/TilesetData.hpp>
#include "Frame.hpp"

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