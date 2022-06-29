loki_create_lib(
  NAME json MODULE core INTERFACE
  HEADERS
  Color.hpp
  Macros.hpp
  Optional.hpp
  Path.hpp
  Rect.hpp
  String.hpp
  Time.hpp
  Vector2.hpp
  PUBLIC_DEPS
  sfml-graphics
  nlohmann_json::nlohmann_json
)
