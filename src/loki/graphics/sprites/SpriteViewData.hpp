#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <loki/graphics/anim/ShapeAnimationData.hpp>
#include "SpriteData.hpp"

namespace loki::gfx {

struct SpriteViewData {
  explicit SpriteViewData(
      const SpriteData& data,
      const std::filesystem::path& cd = std::filesystem::current_path());

  std::map<sf::String, gfx::ShapeAnimationData> animations;
  sf::Texture texture;
};

}  // namespace loki::gfx
