#pragma once

#include <filesystem>

#include <SFML/Graphics.hpp>

#include <loki/core/json/Macros.hpp>
#include <loki/core/json/Vector2.hpp>
#include <loki/system/res/JsonResources.hpp>
#include <loki/system/res/ResourceHandle.hpp>
#include <loki/system/res/SFMLResources.hpp>

#include "Property.hpp"
#include "TerrainData.hpp"
#include "TileData.hpp"

namespace loki::gfx {

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

struct TilesetData : public system::JsonResource<TilesetData> {
  system::ResourceHandle<system::TextureResource> texture;
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

}  // namespace loki::gfx
