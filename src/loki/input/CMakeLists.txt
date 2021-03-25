loki_create_lib(
    NAME input
    HEADERS
        model/InputSettings.hpp
        model/InputState.hpp
        model/InputType.hpp
        model/PlayerConfig.hpp
        service/EventHandler.hpp
    SOURCES
        model/InputSettings.cpp
        model/InputType.cpp
        service/EventHandler.cpp
    PUBLIC_DEPS
        loki::common
        sfml-window
        sfml-system)
