#pragma once

#include <variant>

#include <nlohmann/json.hpp>

namespace nlohmann {

template <typename... Types>
struct adl_serializer<std::variant<Types...>> {
  static void to_json(json& j, const std::variant<Types...>& v) {
    std::visit(
        [&](const auto& x) {
          j["alt_id"] = v.index();
          to_json(j["value"], x);
        },
        v);
  }

  static void from_json(const json& j, std::variant<Types...>& v) {
    v = make_variant<0, Types...>(j.at("alt_id").get<int>(), j.at("value"));
  }

 private:
  template <std::size_t Index, typename, typename... Rest>
  static std::variant<Types...> make_variant(std::size_t index, const json& j) {
    if (Index == index) {
      std::variant<Types...> v{std::in_place_index_t<Index>{}};
      j.get_to(std::get<Index>(v));
      return v;
    }

    if constexpr (sizeof...(Rest) != 0)
      return make_variant<Index + 1, Rest...>(index, j);
    else
      throw std::bad_variant_access{};
  }
};

}  // namespace nlohmann
