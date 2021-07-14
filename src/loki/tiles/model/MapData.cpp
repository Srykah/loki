/*!
 * \file Map.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "MapData.hpp"
#include <fstream>
#include <loki/json/Color.hpp>
#include <nlohmann/json.hpp>

namespace loki::tiles {

MapData::MapData(const std::filesystem::path& filePath,
         const TilesetLoader& tilesetLoader) {
  load(filePath, tilesetLoader);
}

bool MapData::load(const std::filesystem::path& filePath,
               const MapData::TilesetLoader& tilesetLoader) {
  std::ifstream file(filePath);
  nlohmann::json jsonData;
  file >> jsonData;
  for (const auto& tilesetData : std::as_const(jsonData.at("tilesets"))) {
    auto tilesetFilepath = std::filesystem::path{tilesetData.at("source").get<std::string>()};
    tilesets.emplace_back(tilesetLoader(tilesetFilepath));
  }
  gridSize = sf::Vector2u{jsonData.at("width").get<unsigned int>(),
                          jsonData.at("height").get<unsigned int>()};
  for (const auto& layerData : std::as_const(jsonData.at("layers"))) {
    if (layerData.at("type").get<std::string>() == "tilelayer") {
      layers.emplace_back(TileLayerData{layerData});
    } else if (layerData.at("type").get<std::string>() == "objectgroup") {
      layers.emplace_back(ObjectLayerData{layerData});
    }
  }
  if (jsonData.contains("properties")) {
    loadPropertyMap(properties, jsonData.at("properties"));
  }
  if (jsonData.contains("backgroundcolor")) {
    backgroundColor = common::parseHTMLColor(jsonData.at("backgroundcolor").get<std::string>());
  }

  return true;
}

}  // namespace loki::tiles
