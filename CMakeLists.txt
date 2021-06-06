### Basic setup
cmake_minimum_required(VERSION 3.18)
project(loki
        VERSION 0.1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Compile loki as a shared library. If OFF, all dependencies will be linked to statically.")

### Helper functions, modules and macros

# Force out-of-source build (for good practise)
include(cmake/MacroEnsureOutOfSourceBuild.cmake)
MACRO_ENSURE_OUT_OF_SOURCE_BUILD("You must use an out-of-source build.")

# CMake config logging
include(cmake/LoggingHelpers.cmake)

# Installing
include(cmake/InstallHelpers.cmake)

### Dependencies

# Add the cmake folder so the FindSphinx module is found
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

## Libs ROOTs

# JSON
set(nlohmann_json_ROOT "" CACHE PATH "nlohmann/json root directory. Leave blank for system default.")
loki_print_variables(nlohmann_json_ROOT)

# FMT
set(fmt_ROOT "" CACHE PATH "fmt root directory. Leave blank for system default.")
loki_print_variables(fmt_ROOT)

# SFML
set(SFML_ROOT "" CACHE PATH "SFML root directory. Leave blank for system default.")
loki_print_variables(SFML_ROOT)

## Add libs

# JSON
find_package(nlohmann_json 3.9 REQUIRED CONFIG)
if(NOT nlohmann_json_FOUND)
    message(FATAL_ERROR "nlohmann/json not found; You should set nlohmann_json_ROOT to the nlohmann/json path")
endif()
loki_print_variables_with_pattern(nlohmann_json)

# FMT
find_package(fmt 7 REQUIRED CONFIG)
if(NOT fmt_FOUND)
    message(FATAL_ERROR "fmt not found; You should set fmt_ROOT to the fmt path")
endif()
loki_print_variables_with_pattern(fmt)

# SFML
set(SFML_STATIC_LIBRARIES $<NOT:${BUILD_SHARED_LIBS}>)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio CONFIG)
if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found; You should set SFML_ROOT to the SFML path")
endif()
loki_print_variables_with_pattern(SFML)

### Core CMake stuff

set(LOKI_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(src/loki/common)
add_subdirectory(src/loki/anim)
add_subdirectory(src/loki/gui)
add_subdirectory(src/loki/hash)
add_subdirectory(src/loki/input)
add_subdirectory(src/loki/json)
add_subdirectory(src/loki/screens)
add_subdirectory(src/loki/sprites)
add_subdirectory(src/loki/states)
add_subdirectory(src/loki/styles)
add_subdirectory(src/loki/tiles)
add_subdirectory(src/loki/tpl)
add_subdirectory(src/loki/window)
## docs
add_subdirectory(docs)

### Installation (for ease of use with other CMake projects)

# Targets
install(
  EXPORT loki_targets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/loki
  NAMESPACE loki::
  FILE lokiTargets.cmake)

# Config
include(CMakePackageConfigHelpers)
configure_package_config_file( 
  lokiConfig.cmake.in
  lokiConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/loki
  PATH_VARS
    nlohmann_json_DIR
    fmt_DIR
    SFML_DIR)

# Version
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/lokiConfigVersion.cmake
  COMPATIBILITY SameMajorVersion)

# Install Config and ConfigVersion files
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/lokiConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/lokiConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/loki")
