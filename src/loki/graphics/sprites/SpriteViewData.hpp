/*!
 * \file SpriteViewData.hpp.h
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <loki/graphics/anim/ShapeAnimationData.hpp>
#include "SpriteData.hpp"

namespace loki::sprites {

struct SpriteViewData {
  explicit SpriteViewData(
      const SpriteData& data,
      const std::filesystem::path& cd = std::filesystem::current_path());

  std::map<sf::String, anim::ShapeAnimationData> animations;
  sf::Texture texture;
};

}  // namespace loki::sprites
