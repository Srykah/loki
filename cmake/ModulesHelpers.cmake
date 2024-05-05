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

# Installing with structure
function(loki_install_module_headers module)
  cmake_parse_arguments(MODULE "" "" "HEADERS" ${ARGN})
  foreach (header ${MODULE_HEADERS})
    get_filename_component(dir ${header} DIRECTORY)
    get_filename_component(filename ${header} NAME)
    install(
      FILES ${filename}
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/loki/${module}/${dir}
    )
  endforeach ()
  install(TARGETS ${module} EXPORT loki_targets)
endfunction()

# Complete module creation helper
function(loki_create_module module)
  cmake_parse_arguments(MODULE "" "" "HEADERS;SOURCES;PRIVATE_DEPS;PUBLIC_DEPS" ${ARGN})
  add_library(${module} ${MODULE_HEADERS} ${MODULE_SOURCES})
  add_library(loki::${module} ALIAS ${module})
  target_link_libraries(
    ${module}
    PUBLIC "${MODULE_PUBLIC_DEPS}"
    PRIVATE "${MODULE_PRIVATE_DEPS}"
  )
  target_include_directories(
    ${module}
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
  target_compile_features(${module} PUBLIC cxx_std_23)
  set_target_properties(${module} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    COMPILE_WARNING_AS_ERROR YES
  )
  #loki_enable_lto_optional(${module})
  loki_add_module_prefix(${module})
  loki_install_module_headers(${module} FILES ${MODULE_HEADERS})
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