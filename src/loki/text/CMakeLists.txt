loki_create_lib(
	NAME text
	HEADERS
	AnimatedText.hpp
	AnimatedTextStyle.hpp
	Stylesheet.hpp
	SOURCES
	AnimatedText.cpp
	PUBLIC_DEPS
	sfml-graphics
	loki::common
	loki::styles)
