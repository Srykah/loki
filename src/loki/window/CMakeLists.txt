loki_create_lib(
    NAME window
    HEADERS
        Style.hpp
        Window.hpp
    SOURCES
        Style.cpp
        Window.cpp
    PUBLIC_DEPS
				loki::math
        sfml-graphics)
