loki_create_lib(
	NAME math
	HEADERS
	Interpolate.hpp
	LinAlg2D.hpp
	SOURCES
	LinAlg2D.cpp
	INTERNAL_HEADERS
	impl/Interpolate.hxx
	PUBLIC_DEPS
	nlohmann_json::nlohmann_json
	loki::common
	sfml-graphics
	sfml-window
	sfml-system)
