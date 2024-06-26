#pragma once

#if 0
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include <loki/core/utils/Matrix.hpp>

#include "Property.hpp"

namespace loki::graphics {

struct TileLayerData {
  int id;
  std::string name;
  Matrix<int> data;
  PropertyMap properties;
  float opacity;
  bool visible;
};

void to_json(nlohmann::json& j, const TileLayerData& tld);
void from_json(const nlohmann::json& j, TileLayerData& tld);

}  // namespace loki::graphics
#endif