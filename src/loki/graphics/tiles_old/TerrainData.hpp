#pragma once

#include <nlohmann/json.hpp>

#include "Property.hpp"

namespace loki::graphics {

struct TerrainData {
  std::string name;
  PropertyMap properties;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TerrainData, name, properties)

}  // namespace loki::graphics
