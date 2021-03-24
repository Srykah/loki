loki_create_lib(
    NAME common
    HEADERS
        Color.hpp
        IterAadapters.hpp
        Matrix.hpp
        Matrix.inl
        Random.hpp
    SOURCES
        Random.cpp
    PUBLIC_DEPS
        sfml-graphics
        sfml-window
        sfml-system
        nlohmann_json::nlohmann_json)