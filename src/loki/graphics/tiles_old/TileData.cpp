#include "TileData.hpp"

namespace loki::graphics {

void from_json(const nlohmann::json& j, TileData& td) {
  if (j.contains("animation")) {
    j.at("animation").get_to(td.animation);
  }
  if (j.contains("properties")) {
    j.at("properties").get_to(td.properties);
  }
  if (j.contains("terrain")) {
    j.at("terrain").get_to(td.terrain.emplace());
    /*const auto& terrainData = j.at("terrain");
    td.terrain = std::array{
        terrainData.at(0).get<int>(),
        terrainData.at(1).get<int>(),
        terrainData.at(2).get<int>(),
        terrainData.at(3).get<int>(),
    };*/
  }
}

}  // namespace loki::graphics
