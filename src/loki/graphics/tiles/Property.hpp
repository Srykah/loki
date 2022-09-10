#pragma once

#include <filesystem>
#include <string>
#include <variant>

#include <SFML/Graphics/Color.hpp>
#include <nlohmann/json.hpp>

#include <loki/core/json/Color.hpp>

namespace loki::gfx {

using PropertyData = std::variant<std::string, int, float, bool, sf::Color>;
using PropertyMap = std::map<std::string, PropertyData>;

}  // namespace loki::gfx

namespace nlohmann {

template <>
struct adl_serializer<loki::gfx::PropertyMap> {
  static void from_json(const json& j, loki::gfx::PropertyMap& pm) {
    for (const auto& datum : j) {
      auto name = datum.at("name").get<std::string>();
      auto type = datum.at("type").get<std::string>();
      loki::gfx::PropertyData value;
      if (type == "string") {
        value = datum.at("value").get<std::string>();
      } else if (type == "int") {
        value = datum.at("value").get<int>();
      } else if (type == "float") {
        value = datum.at("value").get<float>();
      } else if (type == "bool") {
        value = datum.at("value").get<bool>();
      } else if (type == "color") {
        value = datum.at("value").get<sf::Color>();
      }
      pm.emplace(std::move(name), std::move(value));
    }
  }

  static void to_json(json& j, const loki::gfx::PropertyMap& pm) {
    for (const auto& [name, datum] : pm) {
      json v;
      v["name"] = name;
      if (std::holds_alternative<std::string>(datum)) {
        v["type"] = "string";
        v["value"] = std::get<std::string>(datum);
      } else if (std::holds_alternative<int>(datum)) {
        v["type"] = "int";
        v["value"] = std::get<int>(datum);
      } else if (std::holds_alternative<float>(datum)) {
        v["type"] = "float";
        v["value"] = std::get<float>(datum);
      } else if (std::holds_alternative<bool>(datum)) {
        v["type"] = "bool";
        v["value"] = std::get<bool>(datum);
      } else if (std::holds_alternative<sf::Color>(datum)) {
        v["type"] = "color";
        v["value"] = std::get<sf::Color>(datum);
      }
      j.emplace_back(std::move(v));
    }
  }
};

}  // namespace nlohmann
