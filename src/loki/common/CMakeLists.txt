loki_create_lib(
    NAME common
    HEADERS
				Interpolate.hpp
				IterAdapters.hpp
        Matrix.hpp
        Matrix.inl
        Random.hpp
	  INTERNAL_HEADERS
				impl/Interpolate.hxx
    SOURCES
        Random.cpp
    PUBLIC_DEPS
        sfml-graphics
        sfml-window
        sfml-system
        nlohmann_json::nlohmann_json)
