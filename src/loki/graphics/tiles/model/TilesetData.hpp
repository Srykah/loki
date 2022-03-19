/*!
 * \file Tileset.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <loki/core/json/Macros.hpp>
#include <loki/core/json/Vector2.hpp>
#include <loki/core/res/JsonResources.hpp>
#include <loki/core/res/ResourceHandle.hpp>
#include <loki/core/res/SFMLResources.hpp>
#include "Property.hpp"
#include "TerrainData.hpp"
#include "TileData.hpp"

namespace loki::tiles {

enum struct ObjectAlignment {
  UNSPECIFIED,
  TOP_LEFT,
  TOP,
  TOP_RIGHT,
  LEFT,
  CENTER,
  RIGHT,
  BOTTOM_LEFT,
  BOTTOM,
  BOTTOM_RIGHT
};

NLOHMANN_JSON_SERIALIZE_ENUM(ObjectAlignment,
                             {
                                 {ObjectAlignment::UNSPECIFIED, nullptr},
                                 {ObjectAlignment::TOP_LEFT, "topleft"},
                                 {ObjectAlignment::TOP, "top"},
                                 {ObjectAlignment::TOP_RIGHT, "topright"},
                                 {ObjectAlignment::LEFT, "left"},
                                 {ObjectAlignment::CENTER, "center"},
                                 {ObjectAlignment::RIGHT, "right"},
                                 {ObjectAlignment::BOTTOM_LEFT, "bottomleft"},
                                 {ObjectAlignment::BOTTOM, "bottom"},
                                 {ObjectAlignment::BOTTOM_RIGHT, "bottomright"},
                             })

struct TilesetData : public res::JsonResource<TilesetData> {
  res::ResourceHandle<res::TextureResource> texture;
  std::string name;
  ObjectAlignment objectAlignment;
  PropertyMap properties;
  sf::Vector2u tileSize;
  sf::Vector2u dimensions;
  std::map<int, TileData> tiles;
  std::map<int, TerrainData> terrains;

  LOKI_RES_JSONRESOURCE_CTOR_DTOR(TilesetData)
  LOKI_RES_JSONRESOURCE_ADD_CHILDREN_TO_HOLDER(texture)
};

void from_json(const nlohmann::json& j, TilesetData& td);

}  // namespace loki::tiles
