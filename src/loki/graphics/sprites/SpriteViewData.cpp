/*!
 * \file SpriteViewData.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "SpriteViewData.hpp"
#include <stdexcept>

namespace loki::sprites {

SpriteViewData::SpriteViewData(const SpriteData& data,
                               const std::filesystem::path& cd) {
  if (!texture.loadFromFile((cd / data.texture.getPath()).string())) {
    throw std::runtime_error("Could not load " +
                             data.texture.getPath().string());
  }
  for (const auto& [animName, animData] : data.animations) {
    animations.emplace(animName, animData);
  }
}

}  // namespace loki::sprites
