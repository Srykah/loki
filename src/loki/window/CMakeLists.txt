loki_create_lib(
    NAME window
    HEADERS
        All.hpp
        Style.hpp
        Window.hpp
    SOURCES
        Style.cpp
        Window.cpp
    PUBLIC_DEPS
        loki::common
        sfml-graphics
        sfml-window
        sfml-system)
