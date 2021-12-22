loki_create_lib(
  NAME anim
  HEADERS AnimationData.hpp AnimationViewData.hpp Animator.hpp Keyframe.hpp
  INTERNAL_HEADERS impl/ADLHelpers.hpp impl/Animator.hxx impl/TemplateHelpers.hpp
  SOURCES AnimationData.cpp AnimationViewData.cpp
  PUBLIC_DEPS loki::common loki::math loki::json sfml-graphics nlohmann_json::nlohmann_json fmt::fmt)
