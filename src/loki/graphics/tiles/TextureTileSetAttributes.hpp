#pragma once

#include <loki/system/res/SFMLResources.hpp>
#include <loki/tiles/TileSetData.hpp>

namespace loki::graphics {

struct TextureTileSetAttribute : public tiles::TileSetAttribute {
  system::ResourceHandle<system::TextureResource> texture;

  void addChildResourcesToHolder(system::ResourceHolder& holder, system::ResourceListener& listener) override {
    holder.add(texture, &listener);
  }

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(TextureTileSetAttribute)
};

}  // namespace loki::graphics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::tiles::TileSetAttribute, loki::graphics::TextureTileSetAttribute)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::TextureTileSetAttribute, texture)
LOKI_REFLECTION_CLASS_END_RTTI(loki::graphics::TextureTileSetAttribute)