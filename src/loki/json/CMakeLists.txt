loki_create_lib(
	NAME json
	HEADERS
	Color.hpp
	Optional.hpp
	Rect.hpp
	String.hpp
	Time.hpp
	Vector2.hpp
	SOURCES
	Color.cpp
	PUBLIC_DEPS
	sfml-graphics
	sfml-window
	sfml-system
	nlohmann_json::nlohmann_json)
