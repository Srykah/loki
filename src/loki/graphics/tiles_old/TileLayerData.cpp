#include "TileLayerData.hpp"

#if 0
namespace loki::graphics {

TileLayerData::TileLayerData(const nlohmann::json& layerData)
    : id(layerData.at("id").get<int>()),
      name(layerData.at("name").get<std::string>()),
      data(layerData.at("width").get<int>(),
           layerData.at("height").get<int>(),
           layerData.at("data").cbegin()),
      opacity(layerData.at("opacity").get<float>()),
      visible(layerData.at("visible").get<bool>()) {
  if (layerData.contains("properties")) {
    loadPropertyMap(properties, layerData.at("properties"));
  }
}
}  // namespace loki::graphics
#endif