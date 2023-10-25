#include "LayerData.hpp"

namespace loki::gfx {

// TileLayerData

void from_json(const core::json& j, TileLayerData& tld) {
  j.at("name").get_to(tld.name);
  auto width = j.at("width").get<std::size_t>();
  auto height = j.at("height").get<std::size_t>();
  auto data = j.at("data").get<std::vector<int>>();
  tld.data = core::Matrix<int>(width, height, data.begin());
  if (j.contains("properties")) {
    j.at("properties").get_to(tld.properties);
  }
  j.at("opacity").get_to(tld.opacity);
  j.at("visible").get_to(tld.visible);
}

void to_json(core::json& j, const TileLayerData& tld) {
  j["type"] = "tilelayer";
  j["name"] = tld.name;
  j["width"] = tld.data.getWidth();
  j["height"] = tld.data.getHeight();
  j["data"] = std::vector<int>{tld.data.begin(), tld.data.end()};
  if (!tld.properties.empty()) {
    j["properties"] = tld.properties;
  }
  j["opacity"] = tld.opacity;
  j["visible"] = tld.visible;
}

// ObjectLayerData

void from_json(const core::json& j, ObjectLayerData& old) {
  j.at("name").get_to(old.name);
  j.at("objects").get_to(old.objects);
}

void to_json(core::json& j, const ObjectLayerData& old) {
  j["type"] = "objectgroup";
  j["name"] = old.name;
  j["objects"] = old.objects;
}

}  // namespace loki::gfx
