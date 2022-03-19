/*!
 * \file Tileset.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TilesetData.hpp"
#include <fstream>

namespace loki::tiles {

void from_json(const nlohmann::json& j, TilesetData& td) {
  td.texture = res::ResourceHandle<res::TextureResource>{
      j.at("image").get<std::string>()};

  j.at("name").get_to(td.name);
  j.at("tilewidth").get_to(td.tileSize.x);
  j.at("tileheight").get_to(td.tileSize.y);
  td.dimensions = sf::Vector2u{
      j.at("imagewidth").get<int>() / td.tileSize.x,
      j.at("imageheight").get<int>() / td.tileSize.y,
  };
  if (j.contains("tiles")) {
    for (const auto& tileData : j.at("tiles")) {
      td.tiles.emplace(tileData.at("id").get<int>(), tileData);
    }
  }
  if (j.contains("properties")) {
    j.at("properties").get_to(td.properties);
  }
}

}  // namespace loki::tiles
