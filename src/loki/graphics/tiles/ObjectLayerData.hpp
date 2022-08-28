#pragma once

#if 0
#include <string>
#include <vector>
#include "ObjectData.hpp"

namespace loki::gfx {

struct ObjectLayerData {
  std::string name;
  std::vector<ObjectData> objects;

  ObjectLayerData(const nlohmann::json& data);
};

}  // namespace loki::gfx
#endif