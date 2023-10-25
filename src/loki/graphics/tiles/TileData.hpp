#pragma once

#include <optional>
#include <vector>

#include <SFML/System/Time.hpp>

#include <loki/core/json/Macros.hpp>
#include <loki/core/json/Time.hpp>

#include "Property.hpp"

namespace loki::gfx {

struct Frame {
  int tileid = -1;
  sf::Time duration;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Frame, tileid, duration)

struct TileData {
  std::vector<Frame> animation;
  PropertyMap properties;
  std::optional<std::array<int, 4>> terrain;
};

void from_json(const core::json& j, TileData& td);
void to_json(core::json& j, const TileData& td);

}  // namespace loki::gfx
