#pragma once

#include <loki/core/utils/Macros.hpp>
#include <nlohmann/json.hpp>

#define LOKI_JSON_TO(fieldName) loki_json_j[#fieldName] = loki_json_s.fieldName;
#define LOKI_JSON_FROM(fieldName) \
  loki_json_j.at(#fieldName).get_to(loki_json_s.fieldName);

#define LOKI_JSON_SERIALIZE_STRUCT(Struct, ...)    \
  inline void to_json(nlohmann::json& loki_json_j, \
                      const Struct& loki_json_s) { \
    LOKI_CORE_REPEAT(LOKI_JSON_TO, __VA_ARGS__)    \
  }
#define LOKI_JSON_DESERIALIZE_STRUCT(Struct, ...)          \
  inline void from_json(const nlohmann::json& loki_json_j, \
                        Struct& loki_json_s) {             \
    LOKI_CORE_REPEAT(LOKI_JSON_FROM, __VA_ARGS__)          \
  }

#define LOKI_JSON_SERIALIZE_STRUCT_STUB(Struct)                         \
  inline void to_json(nlohmann::json& loki_json_j,                      \
                      const Struct& loki_json_s) {                      \
    throw std::logic_error("Unimplemented to_json for class " #Struct); \
  }
#define LOKI_JSON_DESERIALIZE_STRUCT_STUB(Struct)                         \
  inline void from_json(const nlohmann::json& loki_json_j,                \
                        Struct& loki_json_s) {                            \
    throw std::logic_error("Unimplemented from_json for class " #Struct); \
  }

#define LOKI_JSON_SERIALIZE_ONLY_STRUCT(Struct, ...) \
  LOKI_JSON_SERIALIZE_STRUCT(Struct, __VA_ARGS__)    \
  LOKI_JSON_DESERIALIZE_STRUCT_STUB(Struct)

#define LOKI_JSON_DESERIALIZE_ONLY_STRUCT(Struct, ...) \
  LOKI_JSON_SERIALIZE_STRUCT_STUB(Struct)              \
  LOKI_JSON_DESERIALIZE_STRUCT(Struct, __VA_ARGS__)
