#include "Property.hpp"

#include <loki/core/json/Color.hpp>

namespace loki::gfx {

void loadPropertyMap(PropertyMap& propertyMap, const core::json& propArray) {
  for (const auto& propertyDatum : propArray) {
    auto name = propertyDatum.at("name").get<std::string>();
    auto type = propertyDatum.at("type").get<std::string>();
    PropertyData value;
    if (type == "string") {
      value = propertyDatum.at("value").get<std::string>();
    } else if (type == "int") {
      value = propertyDatum.at("value").get<int>();
    } else if (type == "float") {
      value = propertyDatum.at("value").get<float>();
    } else if (type == "bool") {
      value = propertyDatum.at("value").get<bool>();
    } else if (type == "color") {
      value = core::parseHTMLColor(propertyDatum.at("value").get<std::string>());
    }
    propertyMap.emplace(std::move(name), std::move(value));
  }
}

PropertyMap getPropertyMap(const core::json& propArray) {
  PropertyMap result;
  loadPropertyMap(result, propArray);
  return result;
}

}  // namespace loki::gfx
