/*!
 * \file TerrainData.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <nlohmann/json.hpp>
#include "Property.hpp"

namespace loki::tiles {

struct TerrainData {
  std::string name;
  PropertyMap properties;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TerrainData, name, properties)

}  // namespace loki::tiles
