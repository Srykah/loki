#pragma once

#include <filesystem>
#include <loki/graphics/anim/ShapeAnimationData.hpp>
#include <loki/system/res/JsonResources.hpp>
#include <loki/system/res/ResourceHolder.hpp>
#include <loki/system/res/SFMLResources.hpp>
#include <map>
#include <nlohmann/json.hpp>

namespace loki::gfx {

struct SpriteData : public system::JsonResource<SpriteData> {
  LOKI_RES_JSONRESOURCE_CTOR_DTOR(SpriteData)

  std::map<std::string, gfx::ShapeAnimationData> animations;
  system::ResourceHandle<system::TextureResource> texture;

  LOKI_RES_JSONRESOURCE_ADD_CHILDREN_TO_HOLDER(texture)
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SpriteData, animations, texture)

}  // namespace loki::gfx
