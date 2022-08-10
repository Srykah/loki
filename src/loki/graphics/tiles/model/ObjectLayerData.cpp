/*!
 * \file ObjectLayerData.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "ObjectLayerData.hpp"
#if 0
namespace loki::tiles {

ObjectLayerData::ObjectLayerData(const nlohmann::json& data) {
  data.at("name").get_to(name);
  for (const auto& objData : data.at("objects")) {
    objects.emplace_back(objData.get<ObjectData>());
  }
}

}  // namespace loki::tiles
#endif