add_subdirectory(dylib "${CMAKE_CURRENT_BINARY_DIR}/dylib")
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
set(IMGUI_SFML_IMGUI_DEMO ON)
add_subdirectory(imgui-sfml "${CMAKE_CURRENT_BINARY_DIR}/imgui-sfml")