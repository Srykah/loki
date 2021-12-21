/*!
 * \file TileData.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TileData.hpp"

namespace loki::tiles {

TileData::TileData(const nlohmann::json& jsonData) {
  load(jsonData);
}

bool TileData::load(const nlohmann::json& jsonData) {
  if (jsonData.contains("animation")) {
    for (const auto& frameData : std::as_const(jsonData.at("animation"))) {
      animation.emplace_back(Frame{
          frameData.at("tileid").get<int>(),
          sf::milliseconds(frameData.at("duration").get<int>()),
      });
    }
  }
  if (jsonData.contains("properties")) {
    loadPropertyMap(properties, jsonData.at("properties"));
  }
  if (jsonData.contains("terrain")) {
    const auto& terrainData = jsonData.at("terrain");
    terrain = std::array{
        terrainData.at(0).get<int>(),
        terrainData.at(1).get<int>(),
        terrainData.at(2).get<int>(),
        terrainData.at(3).get<int>(),
    };
  }

  return true;
}

}  // namespace loki::tiles