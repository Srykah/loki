/*!
 * \file Optional.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <nlohmann/json.hpp>
#include <optional>

namespace nlohmann {

template <typename T>
struct adl_serializer<std::optional<T>> {
  static void to_json(json& j, const std::optional<T>& opt) {
    if (!opt.has_value()) {
      j = nullptr;
    } else {
      j = *opt;
    }
  }

  static std::optional<T> from_json(const json& j) {
    if (j.is_null()) {
      return std::nullopt;
    } else {
      return j.get<T>();
    }
  }
};

}  // namespace nlohmann
