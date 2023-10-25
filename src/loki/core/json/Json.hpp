#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>

namespace loki::core {

template <class JsonType, class SerializedType>
class ReflectionSerializer;
/*{
  void from_json(const JsonType& j, SerializedType& serialized) {

  }
  void to_json(JsonType& j, const SerializedType& serialized) {

  }
};*/

using json = nlohmann::basic_json<std::unordered_map,
                                  std::vector,
                                  std::u8string,
                                  bool,
                                  std::int32_t,
                                  std::uint32_t,
                                  float,
                                  std::allocator,
                                  ReflectionSerializer,
                                  std::vector<std::byte>>;

}  // namespace loki::core