loki_create_lib(
  NAME anim MODULE graphics INTERFACE
  HEADERS
  ShapeAnimationData.hpp
  ShapeAnimator.hpp
  INTERNAL_HEADERS
  impl/ADLHelpers.hpp
  impl/ShapeAnimator.hxx
  impl/TemplateHelpers.hpp
  PUBLIC_DEPS
  loki::utils
  loki::math
  loki::json
  sfml-graphics
  nlohmann_json::nlohmann_json
)
