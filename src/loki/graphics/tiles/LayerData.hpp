#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include <loki/core/json/Variant.hpp>
#include <loki/core/utils/Matrix.hpp>

#include "ObjectData.hpp"
#include "Property.hpp"

namespace loki::gfx {

// TileLayerData

struct TileLayerData {
  std::string name;
  core::Matrix<int> data;
  PropertyMap properties;
  float opacity;
  bool visible;
};

void from_json(const core::json& j, TileLayerData& tld);
void to_json(core::json& j, const TileLayerData& tld);

// ObjectLayerData

struct ObjectLayerData {
  std::string name;
  std::vector<ObjectData> objects;
};

void from_json(const core::json& j, ObjectLayerData& old);
void to_json(core::json& j, const ObjectLayerData& old);

// LayerData

using LayerData = std::variant<TileLayerData, ObjectLayerData>;

}  // namespace loki::gfx
