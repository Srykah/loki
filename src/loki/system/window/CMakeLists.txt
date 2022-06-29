loki_create_lib(
  NAME window MODULE system
  HEADERS
  Style.hpp
  Window.hpp
  SOURCES
  Style.cpp
  Window.cpp
  PUBLIC_DEPS
  loki::math
  sfml-graphics
)
