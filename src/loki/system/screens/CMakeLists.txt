loki_create_lib(
  NAME screens
  HEADERS
    Screen.hpp
    ScreenStack.hpp
    Signal.hpp
	INTERNAL_HEADERS
	  impl/Screen.hxx
  SOURCES
    Screen.cpp
    ScreenStack.cpp
  PUBLIC_DEPS
    loki::common
    loki::hash
    sfml-graphics
)
