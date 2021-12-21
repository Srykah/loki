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
  TerrainData() = default;
  explicit TerrainData(const nlohmann::json& jsonData);

  bool load(const nlohmann::json& jsonData);

  std::string name;
  PropertyMap properties;
};

}  // namespace loki::tiles
