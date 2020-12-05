/*!
 * \file TerrainData.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TerrainData.hpp"

namespace loki::tiles {

TerrainData::TerrainData(const nlohmann::json& jsonData) {
  load(jsonData);
}

bool TerrainData::load(const nlohmann::json& jsonData) {
  name = jsonData.at("name").get<std::string>();
  if (jsonData.contains("properties")) {
    loadPropertyMap(properties, jsonData.at("properties"));
  }

  return true;
}

}