loki_create_lib(
	NAME cutscene
	HEADERS
	All.hpp
	TimedAction.hpp
	SOURCES
	dummy.cpp
	PUBLIC_DEPS
	loki::common
	sfml-graphics
	sfml-window
	sfml-system
)
