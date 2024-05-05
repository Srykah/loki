#pragma once

#include <filesystem>
#include <map>

#include <loki/system/res/LogicResource.hpp>
#include <loki/system/res/ResourceHandle.hpp>
#include <loki/system/res/SFMLResources.hpp>
#include <loki/graphics/anim/ShapeAnimationData.hpp>

namespace loki::graphics {

struct SpriteData {
  std::map<std::string, ShapeAnimationData> animations;
  system::ResourceHandle<system::TextureResource> texture;

  LOKI_REFLECTION_CLASS_DECLARE(SpriteData)
};

struct SpriteDataResource : public system::LogicResource<SpriteData> {
  LOKI_LOGICRESOURCE_ADD_CHILDREN_TO_HOLDER(texture)
};

}  // namespace loki::graphics

LOKI_REFLECTION_CLASS_BEGIN(loki::graphics::SpriteData)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::SpriteData, animations)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::SpriteData, texture)
LOKI_REFLECTION_CLASS_END()

LOKI_REFLECTION_CLASS_BEGIN(loki::graphics::SpriteDataResource)
LOKI_REFLECTION_CLASS_END()