/*!
 * \file Tileset.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TilesetData.hpp"
#include <fstream>

namespace loki::tiles {

TilesetData::TilesetData(const std::filesystem::path &path) {
  load(path);
}

bool TilesetData::load(const std::filesystem::path& path) {
  nlohmann::json json;
  std::ifstream fs(path);
  fs >> json;

  const auto imageFilename = json.at("image").get<std::string>();
  if (!texture.loadFromFile((path.parent_path() / imageFilename).string())) {
    return false;
  }
  name = json.at("name").get<std::string>();
  tileSize = sf::Vector2u {
      json.at("tilewidth").get<unsigned int>(),
      json.at("tileheight").get<unsigned int>(),
  };
  dimensions = sf::Vector2u {
      json.at("imagewidth").get<unsigned int>() / tileSize.x,
      json.at("imageheight").get<unsigned int>() / tileSize.y,
  };
  for (const auto& tileData : std::as_const(json.at("tiles"))) {
    tiles.emplace(tileData.at("id").get<int>(), tileData);
  }
  if (json.contains("properties")) {
    loadPropertyMap(properties, json.at("properties"));
  }

  return true;
}

}