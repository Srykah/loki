/*!
 * \file AnimationData.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "AnimationData.hpp"

namespace loki::sprites {

AnimationData::AnimationData(const nlohmann::json& jsonData, const std::filesystem::path& cd) {
  load(jsonData, cd);
}
bool AnimationData::load(const nlohmann::json& jsonData, const std::filesystem::path& cd) {
  repeated = jsonData.value("repeat", repeated);
  if (jsonData.contains("/meta/image"_json_pointer)) {
    texture = sf::Texture {};
    auto textureFilename = (cd / jsonData.at("/meta/image"_json_pointer).get<std::string>()).string();
    texture.value().loadFromFile(textureFilename);
  }
  for (const auto& frameData : jsonData.at("frames")) {
    const auto& rectData = frameData.at("rect");
    sf::IntRect rect {
        rectData.at("x").get<int>(),
        rectData.at("y").get<int>(),
        rectData.at("w").get<int>(),
        rectData.at("h").get<int>(),
    };
    const auto& originData = frameData.at("origin");
    sf::Vector2f origin {
        originData.at("x").get<float>(),
        originData.at("y").get<float>(),
    };
    auto duration = sf::milliseconds(frameData.at("duration").get<int>());
    frames.emplace_back(FrameData { rect, origin, duration });
  }

  return true;
}

}
