loki_create_lib(
  NAME json
  INTERFACE
  HEADERS Color.hpp Optional.hpp Rect.hpp String.hpp Time.hpp Vector2.hpp
  PUBLIC_DEPS sfml-graphics nlohmann_json::nlohmann_json)
