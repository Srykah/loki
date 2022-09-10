#pragma once

#include <filesystem>

#include <nlohmann/json.hpp>

namespace nlohmann {

template <>
struct adl_serializer<std::filesystem::path> {
  static void to_json(json& j, const std::filesystem::path& path) {
    if (path.empty()) {
      j = nullptr;
    } else {
      j = path.generic_u8string();
    }
  }

  static void from_json(const json& j, std::filesystem::path& path) {
    if (j.is_null()) {
      path.clear();
    } else {
      path = std::filesystem::u8path(j.get<std::string>());
    }
  }
};

}  // namespace nlohmann
