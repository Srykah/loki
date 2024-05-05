#pragma once

#include <filesystem>
#include <vector>
#include <SFML/System/Vector2.hpp>

namespace loki::graphics {

struct TileSetData {
    std::filesystem::path texturePath;
    sf::Vector2u tileSize;
};

struct MapData {
  TileSetData tileset;
  sf::Vector2u mapSize;
  std::vector<int> tiles;
};

}