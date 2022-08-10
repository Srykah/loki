/*!
 * \file SpriteData.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <filesystem>
#include <loki/graphics/anim/ShapeAnimationData.hpp>
#include <loki/system/res/JsonResources.hpp>
#include <loki/system/res/ResourceHolder.hpp>
#include <loki/system/res/SFMLResources.hpp>
#include <map>
#include <nlohmann/json.hpp>

namespace loki::sprites {

struct SpriteData : public res::JsonResource<SpriteData> {
  LOKI_RES_JSONRESOURCE_CTOR_DTOR(SpriteData)

  std::map<std::string, anim::ShapeAnimationData> animations;
  res::ResourceHandle<res::TextureResource> texture;

  LOKI_RES_JSONRESOURCE_ADD_CHILDREN_TO_HOLDER(texture)
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SpriteData, animations, texture)

}  // namespace loki::sprites
