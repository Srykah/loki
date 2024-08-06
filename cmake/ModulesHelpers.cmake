# Helpers
include(GNUInstallDirs)
include(CMakePrintHelpers)
#include(LTOHelpers)

# Lib prefixing
function(loki_add_module_prefix module)
  get_target_property(module_prefix ${module} PREFIX)
  if (NOT module_prefix)
    set(module_prefix loki-)
  else ()
    set(module_prefix ${module_prefix}loki-)
  endif ()
  set_target_properties(${module} PROPERTIES PREFIX ${module_prefix})
endfunction()

# Complete module creation helper
function(loki_create_module module)
  cmake_parse_arguments(MODULE "" "" "HEADERS;SOURCES;PRIVATE_DEPS;PUBLIC_DEPS" ${ARGN})
  add_library(${module})
  add_library(loki::${module} ALIAS ${module})
  target_sources(${module} PRIVATE ${MODULE_SOURCES})
  target_sources(${module} PUBLIC
    FILE_SET HEADERS
    FILES ${MODULE_HEADERS})
  target_link_libraries(${module}
    PUBLIC ${MODULE_PUBLIC_DEPS}
    PRIVATE ${MODULE_PRIVATE_DEPS}
  )
  target_include_directories(
    ${module}
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
  #loki_enable_lto_optional(${module})
  loki_add_module_prefix(${module})
  install(TARGETS ${module} EXPORT loki_targets FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${module})
  target_link_libraries(loki INTERFACE loki::${module})
endfunction()

# Create global target
function(loki_create_global_target)
  add_library(loki INTERFACE)
  add_library(loki::loki ALIAS loki)
  install(TARGETS loki EXPORT loki_targets)
endfunction()

# Create all modules
function(loki_create_modules)
  loki_create_global_target()
  foreach (module ${ARGN})
    add_subdirectory(src/loki/${module})
  endforeach ()
endfunction()