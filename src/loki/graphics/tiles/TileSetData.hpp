#pragma once

#include <SFML/System/Vector2.hpp>

#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/system/res/LogicResource.hpp>
#include <loki/system/res/ResourceHandle.hpp>
#include <loki/system/res/SFMLResources.hpp>

namespace loki::graphics {

struct TileSetData {
  sf::Vector2u tileSize;
  system::ResourceHandle<system::TextureResource> texture;
};

struct TileSetDataResource : public system::LogicResource<TileSetData> {
  LOKI_LOGICRESOURCE_ADD_CHILDREN_TO_HOLDER(texture)
};

}  // namespace loki::graphics

LOKI_REFLECTION_CLASS_BEGIN(loki::graphics::TileSetData)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::TileSetData, tileSize)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::TileSetData, texture)
LOKI_REFLECTION_CLASS_END()

LOKI_REFLECTION_CLASS_BEGIN(loki::graphics::TileSetDataResource)
LOKI_REFLECTION_CLASS_END()