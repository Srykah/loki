/*!
 * \file Properties.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Color.hpp>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <variant>

namespace loki::tiles {
using PropertyData = std::variant<std::string, int, float, bool, sf::Color>;
using PropertyMap = std::map<std::string, PropertyData>;

void loadPropertyMap(PropertyMap& propertyMap, const nlohmann::json& propArray);
PropertyMap getPropertyMap(const nlohmann::json& propArray);

}  // namespace loki::tiles