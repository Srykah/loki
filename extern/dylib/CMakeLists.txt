add_library(dylib INTERFACE)
target_sources(dylib INTERFACE include/dylib/dylib.hpp)
target_include_directories(dylib INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")