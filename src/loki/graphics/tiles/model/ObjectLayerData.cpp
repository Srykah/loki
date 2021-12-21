/*!
 * \file ObjectLayerData.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "ObjectLayerData.hpp"

namespace loki::tiles {

ObjectLayerData::ObjectLayerData(const nlohmann::json& data) {
  data.at("name").get_to(name);
  for (const auto& objData : data.at("objects")) {
    objects.emplace_back(loadObjectData(objData));
  }
}

}  // namespace loki::tiles
