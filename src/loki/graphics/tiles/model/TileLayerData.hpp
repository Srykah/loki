/*!
 * \file Layer.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <loki/core/utils/Matrix.hpp>
#include <nlohmann/json.hpp>
#include "Property.hpp"

namespace loki::tiles {

struct TileLayerData {
  explicit TileLayerData(const nlohmann::json& layerData);

  int id;
  std::string name;
  common::Matrix<int> data;
  PropertyMap properties;
  float opacity;
  bool visible;
};

}  // namespace loki::tiles
