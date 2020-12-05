/*!
 * \file SpriteData.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once
#include <optional>
#include <SFML/Graphics.hpp>
#include "AnimationData.hpp"
#include <map>
#include <string>
#include <filesystem>

namespace loki::sprites {

struct SpriteData {
  SpriteData() = default;
  SpriteData(const std::filesystem::path& filepath);

  bool load(const std::filesystem::path& filepath);

  std::map<std::string, AnimationData> animations;
  std::optional<sf::Texture> texture;
};

}
