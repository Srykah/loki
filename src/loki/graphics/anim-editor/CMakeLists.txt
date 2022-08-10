loki_create_lib(
  NAME anim-editor MODULE graphics
  HEADERS
  AnimEditor.hpp
  SOURCES
  AnimEditor.cpp
  PUBLIC_DEPS
  loki::utils
  loki::math
  loki::json
  loki::anim
  sfml-graphics
  nlohmann_json::nlohmann_json
)
