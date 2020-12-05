/*!
 * \file SpriteData.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "SpriteData.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

namespace loki::sprites {

SpriteData::SpriteData(const std::filesystem::path& filepath) {
  load(filepath);
}

bool SpriteData::load(const std::filesystem::path& filepath) {
  std::ifstream fs(filepath);
  nlohmann::json json;
  fs >> json;

  if (json.contains("/meta/image"_json_pointer)) {
    texture = sf::Texture {};
    auto textureFilename = (filepath.parent_path() / json.at("/meta/image"_json_pointer).get<std::string>()).string();
    texture.value().loadFromFile(textureFilename);
  }
  for (auto&& [animName, animData] : json.at("animations").items()) {
    animations.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(animName),
        std::forward_as_tuple(animData, filepath.parent_path()));
  }

  return true;
}

}
