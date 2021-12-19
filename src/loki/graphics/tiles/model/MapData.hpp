/*!
 * \file Map.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include "ObjectLayerData.hpp"
#include "Property.hpp"
#include "TileLayerData.hpp"
#include "TilesetData.hpp"

namespace loki::tiles {
enum struct RenderOrder { RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP };
using LayerData = std::variant<TileLayerData, ObjectLayerData>;
struct MapData {
  using TilesetLoader = std::function<const TilesetData*(const std::filesystem::path&)>;

  MapData() = default;

  MapData(const std::filesystem::path& filePath,
      const TilesetLoader& tilesetLoader);

  bool load(const std::filesystem::path& filePath,
            const TilesetLoader& tilesetLoader);

  sf::Vector2u gridSize;
  std::vector<LayerData> layers;
  PropertyMap properties;
  std::vector<const TilesetData*> tilesets;
  RenderOrder renderOrder;
  sf::Color backgroundColor;
};
}  // namespace loki::tiles