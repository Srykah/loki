loki_create_lib(
	NAME anim
	HEADERS
	All.hpp
	Animated.hpp
	SOURCES
	Animated.cpp
	PUBLIC_DEPS
	loki::common
	sfml-graphics
)
