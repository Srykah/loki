#include "ObjectData.hpp"

namespace loki::gfx {

// TileObjectData

void from_json(const nlohmann::json& j, TileObjectData& tod) {
  if (j.contains("properties")) {
    j.at("properties").get_to(tod.properties);
  }
  j.at("gid").get_to(tod.gid);
  j.at("name").get_to(tod.name);
  j.at("type").get_to(tod.type);
  j.get_to(tod.position);
}

void to_json(nlohmann::json& j, const TileObjectData& tod) {
  j = tod.position;  // keep first
  if (!tod.properties.empty()) {
    j["properties"] = tod.properties;
  }
  j["gid"] = tod.gid;
  j["name"] = tod.name;
  j["type"] = tod.type;
}

// EllipseObjectData

void from_json(const nlohmann::json& j, EllipseObjectData& eod) {
  j.get_to(eod.rect);
  j.at("rotation").get_to(eod.rotation);
}

void to_json(nlohmann::json& j, const EllipseObjectData& eod) {
  j = eod.rect;  // keep first
  j["ellipse"] = true;
  j["rotation"] = eod.rotation;
}

// RectangleObjectData

void from_json(const nlohmann::json& j, RectangleObjectData& rod) {
  j.get_to(rod.rect);
  j.at("rotation").get_to(rod.rotation);
}

void to_json(nlohmann::json& j, const RectangleObjectData& rod) {
  j = rod.rect;  // keep first
  j["rotation"] = rod.rotation;
}

// PointObjectData

void from_json(const nlohmann::json& j, PointObjectData& pod) {
  j.get_to(pod.position);
  j.at("name").get_to(pod.name);
}

void to_json(nlohmann::json& j, const PointObjectData& pod) {
  j = pod.position;  // keep first
  j["point"] = true;
  j["name"] = pod.name;
}

// TextObjectData

void from_json(const nlohmann::json& j, TextObjectData& tod) {
  j.get_to(tod.rect);
  j.at("textbutton").get_to(tod.text);
}

void to_json(nlohmann::json& j, const TextObjectData& tod) {
  j = tod.rect;  // keep first
  j["textbutton"] = tod.text;
}

}  // namespace loki::gfx
