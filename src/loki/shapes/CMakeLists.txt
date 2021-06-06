loki_create_lib(
	NAME shapes
	HEADERS
	Capsule.hpp
	RoundedRectangle.hpp
	SOURCES
	Capsule.cpp
	RoundedRectangle.cpp
	PUBLIC_DEPS
	loki::common
	sfml-graphics
	sfml-window
	sfml-system)
