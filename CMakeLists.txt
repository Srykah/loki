# BASIC SETUP

cmake_minimum_required(VERSION 3.22)
project(
  loki
  VERSION 0.1.0
  LANGUAGES CXX
)


# CONFIG

include(cmake/LocalConfig.cmake OPTIONAL)

# todo make it work
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Compile loki as a shared library. If OFF, all dependencies will be linked to statically." FORCE)


# HELPERS

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(MacroEnsureOutOfSourceBuild)
include(LoggingHelpers)
include(DependenciesHelpers)
include(ModulesHelpers)

# Enforce good practise
macro_ensure_out_of_source_build("You must use an out-of-source build.")


# DEPENDENCIES

set(SFML_STATIC_LIBRARIES $<NOT:${BUILD_SHARED_LIBS}>)
list(APPEND LOKI_DEPS_LIST
  "nlohmann_json, 3.9"
  "fmt, 8"
  "SFML, 2.5, graphics window system audio"
  "ImGui-SFML, 2.3"
  "box2d, 2.4"
  "EnTT, 3.10")
loki_find_all_deps(" ${LOKI_DEPS_LIST}")


# TARGETS

# All modules (+global) target
loki_create_modules(
  core
  graphics
  gui
  system
)


# DOCS

option(LOKI_DOCS "Generate docs with Doxygen and Sphinx." ON)
if (LOKI_DOCS)
  add_subdirectory(docs)
endif ()


# INSTALL

# Targets
install(
  EXPORT loki_targets
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/loki"
  NAMESPACE loki::
  FILE lokiTargets.cmake
)

# Config
include(CMakePackageConfigHelpers)
configure_package_config_file(
  cmake/lokiConfig.cmake.in lokiConfig.cmake
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/loki"
  PATH_VARS fmt_DIR nlohmann_json_DIR SFML_DIR
)

# Version
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/lokiConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion
)
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/lokiConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/loki"
)
