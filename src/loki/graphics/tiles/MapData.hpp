#pragma once

#include <SFML/Graphics.hpp>

#include <loki/system/res/JsonResources.hpp>

#include "LayerData.hpp"
#include "Property.hpp"
#include "TilesetData.hpp"

namespace loki::gfx {

enum struct RenderOrder { RIGHT_UP, RIGHT_DOWN, LEFT_UP, LEFT_DOWN };

NLOHMANN_JSON_SERIALIZE_ENUM(RenderOrder,
                             {
                                 {RenderOrder::RIGHT_UP, "rightUp"},
                                 {RenderOrder::RIGHT_DOWN, "rightDown"},
                                 {RenderOrder::LEFT_UP, "leftUp"},
                                 {RenderOrder::LEFT_DOWN, "leftDown"},
                             })

struct MapData : public system::JsonResource<MapData> {
  sf::Vector2u gridSize;
  std::vector<LayerData> layers;
  PropertyMap properties;
  std::vector<system::ResourceHandle<TilesetData>> tilesets;
  RenderOrder renderOrder;
  sf::Color backgroundColor;

  LOKI_RES_JSONRESOURCE_CTOR_DTOR(MapData)
  LOKI_RES_JSONRESOURCE_ADD_CHILDREN_TO_HOLDER(tilesets);
};

void from_json(const nlohmann::json& j, MapData& md);

}  // namespace loki::gfx
