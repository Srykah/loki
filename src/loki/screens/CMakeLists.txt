loki_create_lib(
    NAME screens
    HEADERS
        All.hpp
        Screen.hpp
        Screen.inl
        ScreenStack.hpp
        Signal.hpp
    SOURCES
        Screen.cpp
        ScreenStack.cpp
    PUBLIC_DEPS
        loki::common
        sfml-graphics
        sfml-window
        sfml-system)