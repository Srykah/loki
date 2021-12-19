/*!
 * \file Tile.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/System/Time.hpp>
#include <optional>
#include <vector>
#include "Property.hpp"

namespace loki::tiles {
struct Frame {
  int tileId;
  sf::Time duration;
};

struct TileData {
  TileData() = default;
  explicit TileData(const nlohmann::json& jsonData);

  bool load(const nlohmann::json& jsonData);

  std::vector<Frame> animation;
  PropertyMap properties;
  std::optional<std::array<int, 4>> terrain;
};
}