loki_create_lib(
    NAME sprites
    HEADERS
        model/SpriteData.hpp
        view/SpriteView.hpp
    SOURCES
        model/SpriteData.cpp
        view/SpriteView.cpp
    PUBLIC_DEPS
        loki::common
        sfml-graphics
        sfml-window
        sfml-system)
