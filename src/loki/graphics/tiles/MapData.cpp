#include "MapData.hpp"

#include <fstream>

#include <nlohmann/json.hpp>

#include <loki/core/json/Color.hpp>

namespace loki::gfx {

void from_json(const core::json& j, MapData& md) {
  for (const auto& tilesetData : std::as_const(j.at("tilesets"))) {
    md.tilesets.emplace_back(md.getPath() / tilesetData.at("source").get<std::string>());
  }
  md.gridSize = sf::Vector2u{j.at("width").get<unsigned int>(), j.at("height").get<unsigned int>()};
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

}  // namespace loki::gfx
