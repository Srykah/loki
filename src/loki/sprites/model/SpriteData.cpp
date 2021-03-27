/*!
 * \file SpriteData.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "SpriteData.hpp"
#include <fstream>

namespace loki::sprites {

SpriteData::SpriteData(const std::filesystem::path& filepath) {
  load(filepath);
}

SpriteData::SpriteData(const nlohmann::json& data) {
  load(data);
}

bool SpriteData::load(const std::filesystem::path& filepath) {
  std::ifstream fs(filepath);
  nlohmann::json data;
  fs >> data;
  return load(data);
}

bool SpriteData::load(const nlohmann::json& data) {
  if (data.contains("/meta/image"_json_pointer)) {
    texture = sf::Texture {};
    auto textureFilename = (filepath.parent_path() / data.at("/meta/image"_json_pointer).get<std::string>()).string();
    texture.value().loadFromFile(textureFilename);
  }
  for (auto&& [animName, animData] : data.at("animations").items()) {
    animations.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(animName),
        std::forward_as_tuple(animData, filepath.parent_path()));
  }

  return true;
}

}
