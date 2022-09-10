#include "TilesetData.hpp"

#include <fstream>

namespace loki::gfx {

void from_json(const nlohmann::json& j, TilesetData& td) {
  td.texture = system::ResourceHandle<system::TextureResource>{
      j.at("image").get<std::string>()};

  j.at("name").get_to(td.name);
  j.at("tilewidth").get_to(td.tileSize.x);
  j.at("tileheight").get_to(td.tileSize.y);
  td.dimensions = sf::Vector2u{
      j.at("imagewidth").get<int>() / td.tileSize.x,
      j.at("imageheight").get<int>() / td.tileSize.y,
  };
  if (j.contains("gfx")) {
    for (const auto& tileData : j.at("gfx")) {
      td.tiles.emplace(tileData.at("id").get<int>(), tileData);
    }
  }
  if (j.contains("properties")) {
    j.at("properties").get_to(td.properties);
  }
}

}  // namespace loki::gfx
