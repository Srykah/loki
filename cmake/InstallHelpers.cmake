# Helpers
include(GNUInstallDirs)
include(CMakePrintHelpers)
#include(LTOHelpers)

# Lib prefixing
macro(loki_add_lib_prefix target)
  get_target_property(LOKI_${target}_PREFIX ${target} PREFIX)
  if (LOKI_${target}_PREFIX STREQUAL LOKI_${target}_PREFIX-NOTFOUND)
    set(LOKI_${target}_PREFIX loki-)
  else ()
    set(LOKI_${target}_PREFIX ${LOKI_${target}_PREFIX}loki-)
  endif ()
  set_target_properties(${target} PROPERTIES PREFIX ${LOKI_${target}_PREFIX})
endmacro()

# Installing with structure
function(loki_target_install_files target module)
  cmake_parse_arguments(LIB "" "" "FILES" ${ARGN})
  foreach (file ${LIB_FILES})
    get_filename_component(dir ${file} DIRECTORY)
    install(
      FILES ${file}
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/loki/${module}/${target}/${dir}
    )
  endforeach ()
endfunction()

# Complete lib creation helper
function(loki_create_lib)
  cmake_parse_arguments(
    LIB
    "INTERFACE"
    "NAME;MODULE"
    "HEADERS;INTERNAL_HEADERS;SOURCES;PRIVATE_DEPS;PUBLIC_DEPS;INTERFACE_DEPS"
    ${ARGN}
  )
  if (LIB_INTERFACE)
    if (DEFINED LIB_SOURCES AND NOT LIB_SOURCES STREQUAL "")
      message(FATAL_ERROR "Interface library can't have .cpp files")
    endif ()
    if (DEFINED LIB_PRIVATE_DEPS AND NOT LIB_PRIVATE_DEPS STREQUAL "")
      message(FATAL_ERROR "Interface library can't have private dependencies")
    endif ()
    add_library(
      ${LIB_NAME} INTERFACE ${LIB_HEADERS} ${LIB_INTERNAL_HEADERS}
    )
    target_compile_features(${LIB_NAME} INTERFACE cxx_std_20)
    target_link_libraries(
      ${LIB_NAME} INTERFACE ${LIB_PUBLIC_DEPS} ${LIB_INTERFACE_DEPS}
    )
  else ()
    add_library(
      ${LIB_NAME} ${LIB_HEADERS} ${LIB_INTERNAL_HEADERS} ${LIB_SOURCES}
    )
    target_compile_features(${LIB_NAME} PUBLIC cxx_std_20)
    target_link_libraries(
      ${LIB_NAME}
      PUBLIC "${LIB_PUBLIC_DEPS}"
      INTERFACE "${LIB_INTERFACE_DEPS}"
      PRIVATE "${LIB_PRIVATE_DEPS}"
    )
  endif ()
  #loki_enable_lto_optional(${LIB_NAME})
  set_target_properties(${LIB_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    )
  add_library(loki::${LIB_NAME} ALIAS ${LIB_NAME})
  target_include_directories(
    ${LIB_NAME}
    INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
  loki_add_lib_prefix(${LIB_NAME})
  loki_target_install_files(
    ${LIB_NAME} ${LIB_MODULE} FILES ${LIB_HEADERS} ${LIB_INTERNAL_HEADERS}
  )
  install(TARGETS ${LIB_NAME} EXPORT loki_targets)
  target_link_libraries(${LIB_MODULE} INTERFACE loki::${LIB_NAME})
endfunction()

# Create all-in-one target
function(loki_create_all_target)
  add_library(all_libs INTERFACE)
  add_library(loki::all_libs ALIAS all_libs)
  install(TARGETS all_libs EXPORT loki_targets)
endfunction()

# Create all modules
function(loki_create_modules)
  loki_create_all_target()
  foreach (module ${ARGN})
    add_library(${module} INTERFACE)
    add_library(loki::${module} ALIAS ${module})
    install(TARGETS ${module} EXPORT loki_targets)
    target_link_libraries(all_libs INTERFACE loki::${module})
    add_subdirectory(src/loki/${module})
  endforeach ()
endfunction()