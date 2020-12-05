/*!
 * \file AnimationData.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <optional>
#include <filesystem>

namespace loki::sprites {

struct FrameData {
  sf::IntRect rect;
  sf::Vector2f origin;
  sf::Time duration;
};

struct AnimationData {
  AnimationData() = default;
  explicit AnimationData(const nlohmann::json& jsonData, const std::filesystem::path& cd = std::filesystem::path());

  bool load(const nlohmann::json& jsonData, const std::filesystem::path& cd = std::filesystem::path());

  std::optional<sf::Texture> texture;
  std::vector<FrameData> frames;
};

}
