/*!
 * \file Map.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "MapData.hpp"
#include <fstream>
#include <loki/core/json/Color.hpp>
#include <nlohmann/json.hpp>

namespace loki::tiles {

void from_json(const nlohmann::json& j, MapData& md) {
  for (const auto& tilesetData : std::as_const(j.at("tilesets"))) {
    md.tilesets.emplace_back(md.getPath() /
                             tilesetData.at("source").get<std::string>());
  }
  md.gridSize = sf::Vector2u{j.at("width").get<unsigned int>(),
                             j.at("height").get<unsigned int>()};
  for (const auto& layerData : j.at("layers")) {
    layerData.get_to(md.layers.emplace_back());
  }
  if (j.contains("properties")) {
    j.at("properties").get_to(md.properties);
  }
  if (j.contains("backgroundcolor")) {
    j.at("backgroundcolor").get_to(md.backgroundColor);
  }
}

}  // namespace loki::tiles
