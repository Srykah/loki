#include "ObjectLayerData.hpp"

#if 0
namespace loki::gfx {

ObjectLayerData::ObjectLayerData(const core::json& data) {
  data.at("name").get_to(name);
  for (const auto& objData : data.at("objects")) {
    objects.emplace_back(objData.get<ObjectData>());
  }
}

}  // namespace loki::gfx
#endif