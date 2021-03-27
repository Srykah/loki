/*!
 * \file SpriteData.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once
#include <optional>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <loki/anim/AnimationData.hpp>
#include <map>
#include <string>
#include <filesystem>

namespace loki::sprites {

struct SpriteData {
  SpriteData() = default;
  explicit SpriteData(const std::filesystem::path& filepath);
  explicit SpriteData(const nlohmann::json& data);

  bool load(const std::filesystem::path& filepath);
  bool load(const nlohmann::json& data);

  std::map<std::string, anim::AnimationData> animations;
  sf::Texture texture;
};

}
