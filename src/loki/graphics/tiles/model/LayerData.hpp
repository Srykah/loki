/*!
 * \file Layer.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <loki/core/utils/Matrix.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "ObjectData.hpp"
#include "Property.hpp"

namespace loki::tiles {

// TileLayerData

struct TileLayerData {
  std::string name;
  Matrix<int> data;
  PropertyMap properties;
  float opacity;
  bool visible;
};

void from_json(const nlohmann::json& j, TileLayerData& tld);
void to_json(nlohmann::json& j, const TileLayerData& tld);

// ObjectLayerData

struct ObjectLayerData {
  std::string name;
  std::vector<ObjectData> objects;
};

void from_json(const nlohmann::json& j, ObjectLayerData& old);
void to_json(nlohmann::json& j, const ObjectLayerData& old);

// LayerData

using LayerData = std::variant<TileLayerData, ObjectLayerData>;

void from_json(const nlohmann::json& j, loki::tiles::LayerData& ld) {
  const auto& type = j.at("type").get<std::string>();
  if (type == "tilelayer") {
    loki::tiles::TileLayerData tld;
    j.get_to(tld);
    ld = tld;
  } else if (type == "objectgroup") {
    loki::tiles::ObjectLayerData old;
    j.get_to(old);
    ld = old;
  }
}

void to_json(nlohmann::json& j, const loki::tiles::LayerData& ld) {
  std::visit([&j](const auto& v) { loki::tiles::to_json(j, v); }, ld);
}

}  // namespace loki::tiles
