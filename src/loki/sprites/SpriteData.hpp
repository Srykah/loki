/*!
 * \file SpriteData.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once
#include <SFML/System/String.hpp>
#include <filesystem>
#include <loki/anim/AnimationData.hpp>
#include <map>
#include <nlohmann/json.hpp>

namespace loki::sprites {

struct SpriteData {
  std::map<sf::String, anim::AnimationData> animations;
  std::filesystem::path texturePath;
};

void to_json(nlohmann::json& json, const SpriteData& data);
void from_json(const nlohmann::json& json, SpriteData& data);

}  // namespace loki::sprites
