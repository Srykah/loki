# Helpers
include(GNUInstallDirs)
include(CMakePrintHelpers)

# Lib prefixing
macro(loki_add_lib_prefix target)
    get_target_property(LOKI_${target}_PREFIX ${target} PREFIX)
    if (LOKI_${target}_PREFIX STREQUAL LOKI_${target}_PREFIX-NOTFOUND)
        set(LOKI_${target}_PREFIX loki-)
    else()
        set(LOKI_${target}_PREFIX ${LOKI_${target}_PREFIX}loki-)
    endif()
    set_target_properties(${target} PROPERTIES PREFIX ${LOKI_${target}_PREFIX})
endmacro()

# Installing with structure
function(loki_target_install_files target)
    foreach (file ${ARGN})
        get_filename_component(dir ${file} DIRECTORY)
        install(FILES ${file} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/loki/${target}/${dir})
    endforeach()
endfunction()

# Configuring All includes header
function(loki_configure_all_hpp)
    cmake_parse_arguments(LIB "" "" "HEADERS" ${ARGN})
    list(TRANSFORM LIB_HEADERS REPLACE ".+" "#include \"\\0\"" OUTPUT_VARIABLE LIB_INCLUDES)
    list(JOIN LIB_INCLUDES "\n" LIB_ALL_INCLUDES)
    configure_file(${PROJECT_SOURCE_DIR}/cmake/All.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/All.hpp @ONLY)
endfunction()

# Complete lib creation helper
function(loki_create_lib)
    cmake_parse_arguments(LIB "INTERFACE" "NAME" "HEADERS;INTERNAL_HEADERS;SOURCES;PRIVATE_DEPS;PUBLIC_DEPS;INTERFACE_DEPS" ${ARGN})
    loki_configure_all_hpp(HEADERS ${LIB_HEADERS})
    if (LIB_INTERFACE)
        if (DEFINED LIB_SOURCES AND NOT LIB_SOURCES STREQUAL "")
            message(FATAL_ERROR "Interface library can't have .cpp files")
        endif ()
        if (DEFINED LIB_PRIVATE_DEPS AND NOT LIB_PRIVATE_DEPS STREQUAL "")
            message(FATAL_ERROR "Interface library can't have private dependencies")
        endif ()
        add_library(${LIB_NAME} INTERFACE)
        target_sources(${LIB_NAME} INTERFACE ${LIB_HEADERS} ${LIB_INTERNAL_HEADERS} All.hpp)
        target_link_libraries(${LIB_NAME} INTERFACE ${LIB_PUBLIC_DEPS} ${LIB_INTERFACE_DEPS})
    else ()
        add_library(${LIB_NAME})
        target_sources(${LIB_NAME}
          PUBLIC ${LIB_HEADERS} All.hpp
          INTERFACE ${LIB_INTERNAL_HEADERS}
          PRIVATE ${LIB_SOURCES})
        target_link_libraries(${LIB_NAME}
          PUBLIC "${LIB_PUBLIC_DEPS}"
          INTERFACE "${LIB_INTERFACE_DEPS}"
          PRIVATE "${LIB_PRIVATE_DEPS}")
    endif ()
    add_library(loki::${LIB_NAME} ALIAS ${LIB_NAME})
    target_include_directories(${LIB_NAME} INTERFACE
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
    loki_add_lib_prefix(${LIB_NAME})
    loki_target_install_files(${LIB_NAME} ${LIB_HEADERS} ${LIB_INTERNAL_HEADERS} All.hpp)
    install(TARGETS ${LIB_NAME} EXPORT loki_targets)
endfunction()

function(loki_create_all_target LOKI_MODULE_LIST)
    cmake_print_variables(LOKI_MODULE_LIST)
    add_library(all_libs INTERFACE)
    add_library(loki::all_libs ALIAS all_libs)
    list(TRANSFORM LOKI_MODULE_LIST PREPEND "loki::" OUTPUT_VARIABLE LOKI_MODULE_ALIAS_LIST)
    target_link_libraries(all_libs INTERFACE ${LOKI_MODULE_ALIAS_LIST})
    install(TARGETS all_libs EXPORT loki_targets)
endfunction()
