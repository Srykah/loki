# BASIC SETUP

cmake_minimum_required(VERSION 3.30)
project(
  loki
  VERSION 0.1.0
  LANGUAGES CXX
)


# CONFIG

include(cmake/LocalConfig.cmake OPTIONAL)

# todo make it work
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libs" FORCE)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON CACHE BOOL "Export all symbols in dlls" FORCE)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (WIN32)
  add_compile_definitions(NOMINMAX)
endif ()


# HELPERS

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(MacroEnsureOutOfSourceBuild)
include(LoggingHelpers)
include(DependenciesHelpers)
include(ModulesHelpers)

# Enforce good practise
macro_ensure_out_of_source_build("You must use an out-of-source build.")


# DEPENDENCIES

# We use CPM for dependencies
include(CPM)

# Box2d
set(BOX2D_BUILD_DOCS OFF)
set(BOX2D_BUILD_TESTBED OFF)
set(BOX2D_BUILD_UNIT_TESTS OFF)
set(BOX2D_USER_SETTINGS OFF)
CPMAddPackage(URI "gh:erincatto/box2d#v2.4.2")

# Dylib
set(DYLIB_BUILD_TESTS OFF)
set(DYLIB_WARNING_AS_ERRORS OFF)
CPMAddPackage(URI "gh:martin-olivier/dylib#v2.2.1")

# EnTT
set(ENTT_BUILD_DOCS OFF)
set(ENTT_BUILD_TESTING OFF)
set(ENTT_BUILD_TOOLS OFF)
set(ENTT_INCLUDE_HEADERS ON)
set(ENTT_INCLUDE_NATVIS ON)
set(ENTT_USE_CLANG_TIDY OFF)
# set(ENTT_USE_LIBCPP ???)
set(ENTT_USE_SANITIZER OFF)
CPMAddPackage(URI "gh:skypjack/entt#v3.13.2")

# SFML
set(SFML_BUILD_AUDIO ON)
set(SFML_BUILD_GRAPHICS ON)
set(SFML_BUILD_NETWORK ON)
set(SFML_BUILD_WINDOW ON)
set(SFML_BUILD_DOC OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_TEST_SUITE OFF)
set(SFML_INSTALL_PKGCONFIG_FILES ON)
set(SFML_OPENGL_ES OFF) # todo check for mobile version
set(SFML_USE_STATIC_STD_LIBS OFF)
set(SFML_USE_SYSTEM_DEPS OFF)
CPMAddPackage(URI "gh:SFML/SFML#2.6.2")

# yaml-cpp
set(YAML_BUILD_SHARED_LIBS ON)
set(YAML_CPP_BUILD_CONTRIB ON)
set(YAML_CPP_BUILD_TOOLS OFF)
set(YAML_CPP_DISABLE_UNINSTALL OFF)
set(YAML_CPP_FORMAT_SOURCE OFF)
set(YAML_CPP_INSTALL ON)
set(YAML_ENABLE_PIC ON)
set(YAML_MSVC_SHARED_RT ON)
set(YAML_USE_SYSTEM_GTEST ON)
CPMAddPackage(URI "gh:jbeder/yaml-cpp#a83cd31548b19d50f3f983b069dceb4f4d50756d") # fix for cmake > 3.4

# ImGui (set after SFML because of FreeType) (as seen in https://github.com/cpm-cmake/CPM.cmake/wiki/More-Snippets)
CPMAddPackage(URI "gh:ocornut/imgui#v1.91.0-docking@1.91.0" DOWNLOAD_ONLY TRUE)
file(COPY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui/CMakeLists.txt" "${imgui_SOURCE_DIR}/CMakeLists.txt")
set(IMGUI_DEMO ON)
set(IMGUI_DISABLE_FILE_FUNCTIONS OFF)
set(IMGUI_DISABLE_OBSOLETE_FUNCTIONS ON)
set(IMGUI_DISABLE_OBSOLETE_KEYIO ON)
set(IMGUI_ENABLE_ASAN OFF)
set(IMGUI_ENABLE_COVERAGE OFF)
set(IMGUI_ENABLE_FREETYPE ON)
set(IMGUI_ENABLE_STDLIB_SUPPORT ON)
set(IMGUI_ENABLE_TRACY OFF)
set(IMGUI_EXAMPLES OFF)
set(IMGUI_IMPL_DX9 OFF)
set(IMGUI_IMPL_DX10 OFF)
set(IMGUI_IMPL_DX11 OFF)
set(IMGUI_IMPL_DX12 OFF)
set(IMGUI_IMPL_GLFW OFF)
set(IMGUI_IMPL_GLUT OFF)
set(IMGUI_IMPL_METAL OFF)
set(IMGUI_IMPL_OPENGL2 OFF)
set(IMGUI_IMPL_OPENGL3 OFF)
set(IMGUI_IMPL_OSX OFF)
set(IMGUI_IMPL_SDL OFF)
set(IMGUI_IMPL_VULKAN OFF)
set(IMGUI_IMPL_WIN32 OFF)
add_subdirectory("${imgui_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/_deps/imgui-build" EXCLUDE_FROM_ALL SYSTEM)

# ImGui-SFML (set after ImGui & SFML)
set(IMGUI_SFML_DISABLE_OBSOLETE_FUNCTIONS ON)
set(IMGUI_SFML_ENABLE_WARNINGS OFF)
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)
set(IMGUI_SFML_USE_DEFAULT_CONFIG ON)
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(SFML_DIR ${SFML_BINARY_DIR})
CPMAddPackage(URI "gh:SFML/imgui-sfml#v2.6.1")

# Install everything
install(TARGETS box2d yaml-cpp ImGui-SFML EXPORT loki_targets)

# TARGETS

# All modules (+global) target
loki_create_modules(
  core
  editor
  graphics
  gui
  physics
  system
  tiles
)

# APP

add_subdirectory(src/loki-runtime)

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
  PATH_VARS SFML_DIR
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
