loki_create_lib(
    NAME sprites
    HEADERS
        model/AnimationData.hpp
        model/SpriteData.hpp
        view/AnimationView.hpp
        view/SpriteView.hpp
    SOURCES
        model/AnimationData.cpp
        model/SpriteData.cpp
        view/AnimationView.cpp
        view/SpriteView.cpp
    PUBLIC_DEPS
        loki::common
        sfml-graphics
        sfml-window
        sfml-system)
