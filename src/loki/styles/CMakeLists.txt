loki_create_lib(
    NAME styles
    HEADERS
        ShapeStyle.hpp
        TextStyle.hpp
    SOURCES
        ShapeStyle.cpp
        TextStyle.cpp
    PUBLIC_DEPS
        sfml-graphics
				nlohmann_json::nlohmann_json)
