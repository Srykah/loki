# GNUInstallDirs
include(GNUInstallDirs)

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

# Complete lib creation helper
function(loki_create_lib)
    cmake_parse_arguments(LIB "" "NAME" "HEADERS;SOURCES;PRIVATE_DEPS;PUBLIC_DEPS;INTERFACE_DEPS" ${ARGN})
    add_library(${LIB_NAME} ${LIB_HEADERS} ${LIB_SOURCES})
    add_library(loki::${LIB_NAME} ALIAS ${LIB_NAME})
    target_link_libraries(${LIB_NAME}
            PRIVATE "${LIB_PRIVATE_DEPS}"
            PUBLIC "${LIB_PUBLIC_DEPS}"
            INTERFACE "${LIB_INTERFACE_DEPS}")
    target_include_directories(${LIB_NAME} PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
    loki_add_lib_prefix(${LIB_NAME})
    loki_target_install_files(${LIB_NAME} ${LIB_HEADERS})
    install(TARGETS ${LIB_NAME} EXPORT loki_targets)
endfunction()