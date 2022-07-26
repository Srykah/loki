loki_create_lib(
  NAME math MODULE core INTERFACE
  HEADERS
  Interpolate.hpp
  Misc.hpp
  Rect.hpp
  Vector2Ops.hpp
  Vector4.hpp
  INTERNAL_HEADERS
  impl/Interpolate.hxx
  impl/Vector4.hxx
  PUBLIC_DEPS
  sfml-graphics
  nlohmann_json::nlohmann_json
)

if (MSVC)
  target_compile_definitions(math INTERFACE _USE_MATH_DEFINES)
endif ()
