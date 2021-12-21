/*!
 * \file Tileset.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include "Property.hpp"
#include "TerrainData.hpp"
#include "TileData.hpp"

namespace loki::tiles {
enum struct ObjectAlignement {
  UNSPECIFIED,
  TOP_LEFT,
  TOP,
  TOP_RIGHT,
  LEFT,
  CENTER,
  RIGHT,
  BOTTOM_LEFT,
  BOTTOM,
  BOTTOM_RIGHT
};

struct TilesetData {
  TilesetData() = default;
  explicit TilesetData(const std::filesystem::path& path);

  bool load(const std::filesystem::path& path);

  sf::Texture texture;
  std::string name;
  ObjectAlignement objectAlignement;
  PropertyMap properties;
  sf::Vector2u tileSize;
  sf::Vector2u dimensions;
  std::map<int, TileData> tiles;
  std::map<int, TerrainData> terrains;
};
}  // namespace loki::tiles