/*!
 * \file SpriteData.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "SpriteData.hpp"
#include <fstream>

namespace loki::sprites {

void to_json(nlohmann::json& json, const SpriteData& data) {
  json["image"] = data.texturePath;
  for (auto&& [animName, animData] : data.animations) {
    const auto animNameUtf8 = animName.toUtf8();
    const std::string animNameStr(animNameUtf8.begin(), animNameUtf8.end());
    json["animations"][animNameStr] = animData;
  }
}

void from_json(const nlohmann::json& json, SpriteData& data) {
  std::string texturePathStr;
  json.at("image").get_to(texturePathStr);
  data.texturePath = texturePathStr;
  for (auto&& [animName, animJson] : json.at("animations").items()) {
    animJson.get_to(data.animations[animName]);
  }
}

}  // namespace loki::sprites
