loki_create_lib(
  NAME shapes MODULE graphics
  HEADERS
  Capsule.hpp
  RoundedRectangle.hpp
  SOURCES
  Capsule.cpp
  RoundedRectangle.cpp
  PUBLIC_DEPS
  sfml-graphics
)

if (MSVC)
  target_compile_definitions(shapes PRIVATE _USE_MATH_DEFINES)
endif ()
