loki_create_lib(
  NAME math INTERFACE
  HEADERS
  Interpolate.hpp
  Rect.hpp
  Vector2.hpp
  INTERNAL_HEADERS
  impl/Interpolate.hxx
  PUBLIC_DEPS
  sfml-graphics
  nlohmann_json::nlohmann_json
)

if (MSVC)
  target_compile_definitions(math INTERFACE _USE_MATH_DEFINES)
endif ()
