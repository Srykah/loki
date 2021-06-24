loki_create_lib(
    NAME screens
    HEADERS
        Screen.hpp
        Screen.inl
        ScreenStack.hpp
        Signal.hpp
    SOURCES
        Screen.cpp
        ScreenStack.cpp
    PUBLIC_DEPS
        loki::common
				loki::hash
        sfml-graphics)
